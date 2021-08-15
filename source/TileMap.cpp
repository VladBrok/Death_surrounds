#include "precompiled.h"
#include "Tilemap.h"
#include "constants.h"
#include "EnemySpawnerTile.h"
#include "EnemySystem.h"
#include "Entity.h"
#include "Resources.h"
#include "ErrorWindow.h"


Tilemap::Tilemap(const int mapGridSizeX, const int mapGridSizeY)
{
    if (mapGridSizeX > TILEMAP_GRID_SIZE_MAX_X || mapGridSizeY > TILEMAP_GRID_SIZE_MAX_Y)
    {
        throw std::runtime_error("ERROR in Tilemap::Tilemap: map grid size is too large\n");
    }

    createEmptyMap(mapGridSizeX, mapGridSizeY);

    textureSheetFileName = resources::getTilesheetFile();
    textureSheet.loadFromFile(textureSheetFileName);

    mapSize.x = mapGridSizeX * GRID_SIZE;
    mapSize.y = mapGridSizeY * GRID_SIZE;

    initCollisionBox();
    initEnemySpawnerBox();
}


Tilemap::Tilemap(const std::string& fileName)
{
    textureSheetFileName = resources::getTilesheetFile();

    loadFromFile(fileName);

    initCollisionBox();
    initEnemySpawnerBox();
}


Tilemap::~Tilemap()
{
    clearMap();
}


void Tilemap::update(Entity& entity, const float deltaTime, EnemySystem& enemySystem)
{
    updateCollisionWithMapBounds(entity, deltaTime);

    updateTiles(entity, deltaTime, enemySystem);
}


void Tilemap::render(sf::RenderTarget& target, 
                     const sf::View& view,
                     const sf::Vector2i& gridPositionAroundWhichRender,
                     sf::Shader* pShader,
                     const sf::Vector2f& shaderLightPosition,
                     const bool showCollisionBox,
                     const bool showEnemySpawnerBox
                     )
{
    int fromX = 0;
    int toX = (int)map.size();

    int fromY = 0;
    int toY = (int)map[0].size();

    // Calculating the render bounds
    if (gridPositionAroundWhichRender != sf::Vector2i(-1, -1))
    {
        sf::Vector2i gridsOnViewAmount(
                        static_cast<sf::Vector2i>(view.getSize()) / (int)GRID_SIZE
                    );

        fromX = gridPositionAroundWhichRender.x - gridsOnViewAmount.x / 2;
        toX   = gridPositionAroundWhichRender.x + gridsOnViewAmount.x / 2 + 1;

        fromY = gridPositionAroundWhichRender.y - gridsOnViewAmount.y / 2 - 1;
        toY   = gridPositionAroundWhichRender.y + gridsOnViewAmount.y / 2 + 2;


        if (fromX < 0)
        {
            toX += -fromX;
            fromX = 0;
        }
        if (fromY < 0)
        {
            toY += -fromY;
            fromY = 0;
        }
        if (toX > (int)map.size())
        {
            if (fromX >= toX - (int)map.size())
            {
                fromX -= toX - (int)map.size();
            }
            toX = (int)map.size();
        }
        if (toY > (int)map[0].size())
        {
            if (fromY >= toY - (int)map[0].size())
            {
                fromY -= toY - (int)map[0].size();
            }
            toY = (int)map[0].size();
        }
    }
    

    for (int x = fromX; x < toX; ++x)
    {
        for (int y = fromY; y < toY; ++y)
        {
            for (int k = 0; k < (int)map[x][y].size(); ++k)
            {
                renderTile(target, *map[x][y][k], pShader, shaderLightPosition, showCollisionBox, showEnemySpawnerBox);
            }
        }
    }
}


void Tilemap::renderDeferred(sf::RenderTarget& target,                                 
                             sf::Shader* pShader,
                             const sf::Vector2f& shaderLightPosition
                             )
{
    while (!tilesForDeferredRender.empty())
    {
        tilesForDeferredRender.top()->render(target, pShader, shaderLightPosition);
        tilesForDeferredRender.pop();
    }
}


void Tilemap::saveToFile(const std::string& fileName)
{
    /*
        Saving format:
            Map:
                1) map grid size                       - x y.

            Tiles:
                1) tile type                           - type;
                2) tile grid position                  - gridPosX gridPosY;
                3) tile specific (from method getAsString).
    */


    InfoWindow popUpWindow(
        "Info", "Are you sure you want to save the map?\nPrevious map will be deleted.", true
        );
    bool confirmSaving = popUpWindow.run();
    if (!confirmSaving)
    {
        return;
    }

    try
    {
        std::ofstream file;
        file.open(fileName);

        if (!file.is_open())
        {
            throw std::runtime_error("ERROR in Tilemap::saveToFile: unable to save the tile map to the file " + fileName + "\n");
        }

        file << map.size() << ' ' << map[0].size() << '\n';

        for (size_t x = 0; x < map.size(); ++x)
        {
            for (size_t y = 0; y < map[x].size(); ++y)
            {
                for (size_t k = 0; k < map[x][y].size(); ++k)
                {
                    file << map[x][y][k]->getType() << ' '
                         << x << ' ' << y << ' '
                         << map[x][y][k]->getAsString() << ' ';
                }
            }
        } 
        file.close();

    
        // Creating a backup file
        std::ifstream inputFile;
        inputFile.open(fileName);
        std::ofstream backupFile;
        backupFile.open(fileName + std::to_string(time(nullptr)) + "_backup");

        if (!inputFile.is_open() || !backupFile.is_open())
        {
            throw std::runtime_error("ERROR in Tilemap::saveToFile: unable to create a backup file\n");
        }

        backupFile << inputFile.rdbuf();
    }
    catch (const std::runtime_error& err)
    {
        std::cout << err.what() << '\n';

        ErrorWindow errWindow("Map hasn't been saved to file " + fileName + ",\nor backup file hasn't been created.", false);
        errWindow.run();
    }
}


void Tilemap::loadFromFile(const std::string& fileName)
{
    /*
        The loading format is the same as the saving format.
    */
    try
    {
        std::ifstream file;
        file.open(fileName);

        if (!file.is_open())
        {
            throw std::runtime_error("ERROR in Tilemap::loadFromFile: unable to open the file " + fileName + "\n");
        }


        int mapGridSizeX = 0;
        int mapGridSizeY = 0;

        file >> mapGridSizeX >> mapGridSizeY;

        if (mapGridSizeX <= 0 || mapGridSizeY <= 0 || 
            mapGridSizeX > TILEMAP_GRID_SIZE_MAX_X || mapGridSizeY > TILEMAP_GRID_SIZE_MAX_Y)
        {
            file.setstate(std::ios::failbit);
        }

        if (!file.fail())
        {
             clearMap();
             createEmptyMap(mapGridSizeX, mapGridSizeY);
             mapSize = sf::Vector2f(mapGridSizeX * GRID_SIZE, mapGridSizeY * GRID_SIZE);
             textureSheet.loadFromFile(textureSheetFileName);
        }
    


        int gridPosX = 0;
        int gridPosY = 0;
        int type = 0;
        sf::IntRect textureRect(0, 0, (int)GRID_SIZE, (int)GRID_SIZE);
        bool canCollide = false;

        while(file >> type >> gridPosX >> gridPosY)
        {
            // Loading the enemy spawner
            if (type == ENEMY_SPAWNER)
            {
                int enemyType          = 0;
                int enemyTimeToSpawn   = 0;

                file >> textureRect.left >> textureRect.top >> canCollide >> enemyType >> enemyTimeToSpawn;

                map[gridPosX][gridPosY].push_back(
                    new EnemySpawnerTile(
                        gridPosX * GRID_SIZE,
                        gridPosY * GRID_SIZE,
                        textureSheet,
                        textureRect,
                        canCollide,
                        enemyType,
                        enemyTimeToSpawn
                    )
                );
            }

            // Loading the regular tile
            else
            {
                file >> textureRect.left >> textureRect.top >> canCollide;

                map[gridPosX][gridPosY].push_back(
                    new Tile(
                          static_cast<TileType>(type),
                          gridPosX * GRID_SIZE, 
                          gridPosY * GRID_SIZE, 
                          textureSheet,
                          textureRect,
                          canCollide
                    )
                );
            }

            if (file.fail())
            {
                throw std::runtime_error("ERROR in Tilemap::loadFromFile: the data in the file " + fileName + " are damaged. Tilemap is not loaded.\n");
            } 
        }
    
        if (file.fail() && !file.eof())
        {
            throw std::runtime_error("ERROR in Tilemap::loadFromFile: the data in the file " + fileName + " are damaged. Tilemap is not loaded.\n");
        } 

    }
    catch (const std::runtime_error& err)
    {
        std::cout << err.what() << '\n';

        ErrorWindow errWindow("The map couldn't be loaded from the file: \n" + fileName, false);
        errWindow.run();
    }
}


void Tilemap::addTile(const int gridPosX, 
                      const int gridPosY, 
                      const sf::IntRect& textureRect,
                      const bool canCollide,
                      const TileType type
                      )
{
    if (positionsAreCorrect(gridPosX, gridPosY))
    {
        // Preventing the user from adding the same tile at the same position
        if (!map[gridPosX][gridPosY].empty() &&
            map[gridPosX][gridPosY].back()->getTextureRect() == textureRect
            )
        {
            return;
        }

        map[gridPosX][gridPosY].push_back(
            new Tile(
                type,
                gridPosX * GRID_SIZE, 
                gridPosY * GRID_SIZE, 
                textureSheet,
                textureRect,
                canCollide
            )
        );
    }
}


void Tilemap::addEnemySpawnerTile(const int gridPosX,
                                  const int gridPosY,
                                  const sf::IntRect& textureRect,
                                  const bool canCollide,
                                  const int enemyType,
                                  const int enemyTimeToSpawn
                                  )
{
    if (positionsAreCorrect(gridPosX, gridPosY))
    {
        // Preventing the user from adding the enemy spawner on top of the another enemy spawner
        if (!map[gridPosX][gridPosY].empty() && 
            map[gridPosX][gridPosY].back()->getType() == ENEMY_SPAWNER)
        {
            return;
        }

        map[gridPosX][gridPosY].push_back(
            new EnemySpawnerTile(
                gridPosX * GRID_SIZE, 
                gridPosY * GRID_SIZE, 
                textureSheet, 
                textureRect, 
                canCollide,
                enemyType, 
                enemyTimeToSpawn
            )
        );
    }
}


void Tilemap::removeTile(const int gridPosX, const int gridPosY)
{
    if (positionsAreCorrect(gridPosX, gridPosY) &&
        !map[gridPosX][gridPosY].empty())
    {
        delete map[gridPosX][gridPosY].back();
        map[gridPosX][gridPosY].pop_back();
    }
}


const sf::Texture& Tilemap::getTextureSheet() const
{
    return textureSheet;
}


int Tilemap::getNumberOfTilesAtPosition(const sf::Vector2i& gridPosition)
{
    if (positionsAreCorrect(gridPosition.x, gridPosition.y))
    {
        return map[gridPosition.x][gridPosition.y].size();
    }
    return -1;
}


int Tilemap::getTileType(const int gridPosX, const int gridPosY)
{
    if (positionsAreCorrect(gridPosX, gridPosY) && !map[gridPosX][gridPosY].empty())
    {
        return map[gridPosX][gridPosY].back()->getType();
    }

    return -1;
}


const std::string& Tilemap::getTileTypeAsString(const int type)
{
    return Tile::getTypeAsString(static_cast<TileType>(type));
}


const sf::Vector2f& Tilemap::getMapSize() const
{
    return mapSize;
}


bool Tilemap::positionsAreCorrect(const int gridPosX, const int gridPosY) const
{
    return gridPosX >= 0 && gridPosX < (int)map.size() &&
           gridPosY >= 0 && gridPosY < (int)map[gridPosX].size();
}


void Tilemap::clearMap()
{
    for (size_t x = 0; x < map.size(); ++x)
    {
        for (size_t y = 0; y < map[x].size(); ++y)
        {
            for (size_t k = 0; k < map[x][y].size(); ++k)
            {
                delete map[x][y][k];
            }
            map[x][y].clear();
        }
        map[x].clear();
    }
    map.clear();
}


void Tilemap::createEmptyMap(const int mapSizeX, const int mapSizeY)
{
    assert(mapSizeX > 0 && mapSizeY > 0);

    map.resize(
        mapSizeX, 
        std::vector<std::vector<Tile*>>(
            mapSizeY, 
            std::vector<Tile*>(0)
        )
    );
}


void Tilemap::updateCollisionWithMapBounds(Entity& entity, const float deltaTime)
{
    // Left
    if (entity.getNextPositionBounds(deltaTime).left < 0.f)
    {
        entity.setPosition(0.f, entity.getPosition().y);
        entity.stopVelocityX();
    }

    // Right
    else if (entity.getNextPositionBounds(deltaTime).left + entity.getGlobalBounds().width > mapSize.x)
    {
        entity.setPosition(mapSize.x - entity.getGlobalBounds().width, entity.getPosition().y);
        entity.stopVelocityX();
    }

    // Top
    if (entity.getNextPositionBounds(deltaTime).top < 0.f)
    {
        entity.setPosition(entity.getPosition().x, 0.f);
        entity.stopVelocityY();
    }

    // Bottom
    else if (entity.getNextPositionBounds(deltaTime).top + entity.getGlobalBounds().height > mapSize.y)
    {
        entity.setPosition(entity.getPosition().x, mapSize.y - entity.getGlobalBounds().height);
        entity.stopVelocityY();
    }
}


void Tilemap::updateTiles(Entity& entity, const float deltaTime, EnemySystem& enemySystem)
{
    // Calculating the update bounds

    int fromX = entity.getGridPosition().x - 2;
    if (fromX < 0)
    {
        fromX = 0;
    }

    int toX = entity.getGridPosition().x + 4;
    if (toX > (int)map.size())
    {
        toX = map.size();
    }

    int fromY = entity.getGridPosition().y - 2;
    if (fromY < 0)
    {
        fromY = 0;
    }

    int toY = entity.getGridPosition().y + 4;
    if (toY > (int)map[0].size())
    {
        toY = map[0].size();
    }
    

    for (int x = fromX; x < toX; ++x)
    {
        for (int y = fromY; y < toY; ++y)
        {
            for (int k = 0; k < (int)map[x][y].size(); ++k)
            {
                if (map[x][y][k]->getType() == ENEMY_SPAWNER)
                {
                    EnemySpawnerTile* es = dynamic_cast<EnemySpawnerTile*>(map[x][y][k]);
                    if (es)
                    {
                        es->update(enemySystem);
                    }
                }

                // Checking for the intersection
                if (map[x][y][k]->tileCanCollide() &&
                    map[x][y][k]->intersects(entity.getNextPositionBounds(deltaTime))
                   )
                {
                    handleCollision(*map[x][y][k], entity);
                }
            }
        }
    }
}


void Tilemap::handleCollision(const Tile& tile, Entity& entity)
{
    sf::FloatRect entityBounds = entity.getGlobalBounds();
    sf::FloatRect tileBounds   = tile.getGlobalBounds();

    // Checking the collision side of the entity

    // Bottom collision
    if (entityBounds.top < tileBounds.top && 
        entityBounds.top + entityBounds.height < tileBounds.top + tileBounds.height && 
        entityBounds.left < tileBounds.left + tileBounds.width &&
        entityBounds.left + entityBounds.width > tileBounds.left
       )
    {
        entity.stopVelocityY();
        entity.setPosition(entityBounds.left, tileBounds.top - entityBounds.height);
    }

    // Top collision
    else if (entityBounds.top > tileBounds.top && 
             entityBounds.top + entityBounds.height > tileBounds.top + tileBounds.height && 
             entityBounds.left < tileBounds.left + tileBounds.width && 
             entityBounds.left + entityBounds.width > tileBounds.left
           )
    {
        entity.stopVelocityY();
        entity.setPosition(entityBounds.left, tileBounds.top + tileBounds.height);
    }

    // Right collision
    if (entityBounds.left < tileBounds.left &&
        entityBounds.left + entityBounds.width < tileBounds.left + tileBounds.width && 
        entityBounds.top < tileBounds.top + tileBounds.height &&
        entityBounds.top + entityBounds.height > tileBounds.top
       )
    {
        entity.stopVelocityX();
        entity.setPosition(tileBounds.left - entityBounds.width, entityBounds.top);
    }

    // Left collision
    else if (entityBounds.left > tileBounds.left &&
             entityBounds.left + entityBounds.width > tileBounds.left + tileBounds.width &&
             entityBounds.top < tileBounds.top + tileBounds.height && 
             entityBounds.top + entityBounds.height > tileBounds.top
            )
    {
        entity.stopVelocityX();
        entity.setPosition(tileBounds.left + tileBounds.width, entityBounds.top);
    }
}


void Tilemap::renderTile(sf::RenderTarget& target, 
                         Tile& tile,
                         sf::Shader* pShader,
                         const sf::Vector2f& shaderLightPosition,
                         const bool showCollisionBox,
                         const bool showEnemySpawnerBox
                         )
{
    if (tile.getType() == RENDERING_DEFERRED) // Pushing the tile to the stack for deferred render
    {
        tilesForDeferredRender.push(&tile);
    }
    else // Rendering the tile
    {
        tile.render(target, pShader, shaderLightPosition); 
    }


    // Rendering the collision box
    if (tile.tileCanCollide() && showCollisionBox)
    {
        collisionBox.setPosition(tile.getPosition());
        target.draw(collisionBox);
    }

    // Rendering the enemy spawner box
    if (tile.getType() == ENEMY_SPAWNER && showEnemySpawnerBox)
    {
        enemySpawnerBox.setPosition(tile.getPosition());
        target.draw(enemySpawnerBox);
    }
}


void Tilemap::initCollisionBox()
{
    collisionBox.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
    collisionBox.setOutlineColor(sf::Color::Red);
    collisionBox.setOutlineThickness(-1.f);
}


void Tilemap::initEnemySpawnerBox()
{
    enemySpawnerBox.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    enemySpawnerBox.setFillColor(sf::Color::Transparent);
    enemySpawnerBox.setOutlineColor(sf::Color::Magenta);
    enemySpawnerBox.setOutlineThickness(-2.f);
}