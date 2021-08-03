#include "precompiled.h"
#include "Tilemap.h"
#include "constants.h"
#include "EnemySpawnerTile.h"


Tilemap::Tilemap(const int mapSizeX, const int mapSizeY, const int mapSizeZ)
{
    createEmptyMap(mapSizeX, mapSizeY, mapSizeZ);

    textureSheetFileName = "Resources\\Images\\Tiles\\tilesheet.png";
    textureSheet.loadFromFile(textureSheetFileName);

    initCollisionBox();
    initEnemySpawnerBox();

    mapSize.x = mapSizeX * GRID_SIZE;
    mapSize.y = mapSizeY * GRID_SIZE;
    mapSize.z = mapSizeZ * GRID_SIZE;
}


Tilemap::Tilemap(const std::string& fileName)
{
    loadFromFile(fileName);

    initCollisionBox();
    initEnemySpawnerBox();
}


Tilemap::~Tilemap()
{
    clearMap();
}


void Tilemap::update(Entity& entity, const float deltaTime)
{
    updateCollisionWithMapBounds(entity, deltaTime);

    updateTiles(entity, deltaTime);
}


void Tilemap::render(sf::RenderTarget& target, 
                     const sf::Vector2i& gridPositionAroundWhichRender,
                     sf::Shader* pShader,
                     const sf::Vector2f& shaderLightPosition,
                     const bool showCollisionBox,
                     const bool showEnemySpawnerBox 
                     )
{
    // FIXME
    int z = 0;
    

    // Calculating the rendering bounds
    int fromX = gridPositionAroundWhichRender.x - 5;
    if (fromX < 0)
    {
        fromX = 0;
    }
    int toX = gridPositionAroundWhichRender.x + 7;
    if (toX > (int)map.size())
    {
        toX = map.size();
    }

    int fromY = gridPositionAroundWhichRender.y - 4;
    if (fromY < 0)
    {
        fromY = 0;
    }
    int toY = gridPositionAroundWhichRender.y + 5;
    if (toY > (int)map[0].size())
    {
        toY = map[0].size();
    }

    // Rendering the tilemap around the specified grid position
    for (int x = fromX; x < toX; ++x)
    {
        for (int y = fromY; y < toY; ++y)
        {
            for (int k = 0; k < (int)map[x][y][z].size(); ++k)
            {
                if (map[x][y][z][k]->getType() == RENDERING_DEFERRED) // Pushing the tile to the stack for deferred render
                {
                    tilesForDeferredRender.push(map[x][y][z][k]);
                }
                else // Rendering the tile
                {
                    map[x][y][z][k]->render(target, pShader, shaderLightPosition); 
                }


                // Rendering the collision box
                if (map[x][y][z][k]->tileCanCollide() && showCollisionBox)
                {
                    collisionBox.setPosition(map[x][y][z][k]->getPosition());
                    target.draw(collisionBox);
                }

                // Rendering the enemy spawner box
                if (map[x][y][z][k]->getType() == ENEMY_SPAWNER && showEnemySpawnerBox)
                {
                    enemySpawnerBox.setPosition(map[x][y][z][k]->getPosition());
                    target.draw(enemySpawnerBox);
                }
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
                1) map size                            - x y z;
                2) name of the file with texture sheet - textureSheetFileName

            Tiles:
                1) tile type                           - type;
                2) tile grid position                  - gridPosX gridPosY gridPosZ;
                3) tile specific (from method getAsString)
    */

    std::ofstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        std::cout << "ERROR in Tilemap::saveToFile: unable to save the tile map to the file " << fileName << '\n';
        return;
    }

    file << map.size() << ' ' << map[0].size() << ' ' << map[0][0].size() << '\n';
    file << textureSheetFileName << '\n';

    for (size_t x = 0; x < map.size(); ++x)
    {
        for (size_t y = 0; y < map[x].size(); ++y)
        {
            for (size_t z = 0; z < map[x][y].size(); ++z)
            {
                for (size_t k = 0; k < map[x][y][z].size(); ++k)
                {
                    file << map[x][y][z][k]->getType() << ' '
                         << x << ' ' << y << ' '<< z << ' ' 
                         << map[x][y][z][k]->getAsString() << ' ';
                }
            }
        }
    } 
}


void Tilemap::loadFromFile(const std::string& fileName)
{
    /*
        The loading format is the same as the saving format.
    */

    std::ifstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        std::cout << "ERROR in Tilemap::loadFromFile: unable to load the tile map from the file " << fileName << '\n';
        return;
    }


    int mapSizeX = 0;
    int mapSizeY = 0;
    int mapSizeZ = 0;

    file >> mapSizeX >> mapSizeY >> mapSizeZ >> textureSheetFileName;

    if (mapSizeX <= 0 || mapSizeY <= 0 || mapSizeZ <= 0)
    {
        file.setstate(std::ios::failbit);
    }

    if (!file.fail())
    {
         clearMap();
         createEmptyMap(mapSizeX, mapSizeY, mapSizeZ);
         mapSize = sf::Vector3f(mapSizeX * GRID_SIZE, mapSizeY * GRID_SIZE, mapSizeZ * GRID_SIZE);
         textureSheet.loadFromFile(textureSheetFileName);
    }
    


    int gridPosX = 0;
    int gridPosY = 0;
    int gridPosZ = 0;
    int type = 0;
    sf::IntRect textureRect(0, 0, (int)GRID_SIZE, (int)GRID_SIZE);
    bool canCollide = false;

    while(file >> type >> gridPosX >> gridPosY >> gridPosZ)
    {
        // Loading the enemy spawner
        if (type == ENEMY_SPAWNER)
        {
            int enemyType          = 0;
            int enemyAmount        = 0;
            int enemyTimeToSpawn   = 0;
            float enemyMaxDistance = 0;

            file >> textureRect.left >> textureRect.top >> canCollide >> enemyType >> enemyAmount >> enemyTimeToSpawn >> enemyMaxDistance;

            map[gridPosX][gridPosY][gridPosZ].push_back(
                new EnemySpawnerTile(
                    gridPosX * GRID_SIZE,
                    gridPosY * GRID_SIZE,
                    textureSheet,
                    textureRect,
                    canCollide,
                    enemyType,
                    enemyAmount,
                    enemyTimeToSpawn,
                    enemyMaxDistance
                )
            );
        }

        // Loading the regular tile
        else
        {
            file >> textureRect.left >> textureRect.top >> canCollide;

            map[gridPosX][gridPosY][gridPosZ].push_back(
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
            std::cout << "ERROR in Tilemap::loadFromFile: the data in the file " << fileName << " are damaged. Tilemap is not loaded.\n";
            return;
        } 
    }
}


void Tilemap::addTile(const int gridPosX, 
                      const int gridPosY, 
                      const int gridPosZ, 
                      const sf::IntRect& textureRect,
                      const bool canCollide,
                      const TileType type
                      )
{
    if (positionsAreCorrect(gridPosX, gridPosY, gridPosZ))
    {
        // Preventing the user from adding the same tile at the same position
        if (!map[gridPosX][gridPosY][gridPosZ].empty() &&
            map[gridPosX][gridPosY][gridPosZ].back()->getTextureRect() == textureRect
            )
        {
            return;
        }

            map[gridPosX][gridPosY][gridPosZ].push_back(
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
                                  const int gridPosZ,
                                  const sf::IntRect& textureRect,
                                  const bool canCollide,
                                  const int enemyType,
                                  const int enemyAmount,
                                  const int enemyTimeToSpawn,
                                  const float enemyMaxDistance
                                  )
{
    if (positionsAreCorrect(gridPosX, gridPosY, gridPosZ))
    {
        // Preventing the user from adding the enemy spawner on top of the another enemy spawner
        if (!map[gridPosX][gridPosY][gridPosZ].empty() && 
            map[gridPosX][gridPosY][gridPosZ].back()->getType() == ENEMY_SPAWNER)
        {
            return;
        }

        map[gridPosX][gridPosY][gridPosZ].push_back(
            new EnemySpawnerTile(
                gridPosX * GRID_SIZE, 
                gridPosY * GRID_SIZE, 
                textureSheet, 
                textureRect, 
                canCollide,
                enemyType, 
                enemyAmount,
                enemyTimeToSpawn,
                enemyMaxDistance
            )
        );
    }
}


void Tilemap::removeTile(const int gridPosX, const int gridPosY, const int gridPosZ)
{
    if (positionsAreCorrect(gridPosX, gridPosY, gridPosZ) &&
        !map[gridPosX][gridPosY][gridPosZ].empty())
    {
        delete map[gridPosX][gridPosY][gridPosZ].back();
        map[gridPosX][gridPosY][gridPosZ].pop_back();
    }
}


const sf::Texture& Tilemap::getTextureSheet() const
{
    return textureSheet;
}


int Tilemap::getNumberOfTilesAtPosition(const sf::Vector2i& gridPosition, const int layer)
{
    if (positionsAreCorrect(gridPosition.x, gridPosition.y, layer))
    {
        return map[gridPosition.x][gridPosition.y][layer].size();
    }
    return -1;
}


int Tilemap::getTileType(const int gridPosX, const int gridPosY, const int gridPosZ)
{
    if (positionsAreCorrect(gridPosX, gridPosY, gridPosZ) && !map[gridPosX][gridPosY][gridPosZ].empty())
    {
        return map[gridPosX][gridPosY][gridPosZ].back()->getType();
    }

    return -1;
}


const std::string& Tilemap::getTileTypeAsString(const int type)
{
    return Tile::getTypeAsString(static_cast<TileType>(type));
}


const sf::Vector3f& Tilemap::getMapSize() const
{
    return mapSize;
}


bool Tilemap::positionsAreCorrect(const int gridPosX, const int gridPosY, const int gridPosZ) const
{
    return gridPosX >= 0 && gridPosX < (int)map.size() &&
           gridPosY >= 0 && gridPosY < (int)map[gridPosX].size() &&
           gridPosZ >= 0 && gridPosZ < (int)map[gridPosX][gridPosY].size();
}


void Tilemap::clearMap()
{
    for (size_t x = 0; x < map.size(); ++x)
    {
        for (size_t y = 0; y < map[x].size(); ++y)
        {
            for (size_t z = 0; z < map[x][y].size(); ++z)
            {
                for (size_t k = 0; k < map[x][y][z].size(); ++k)
                {
                    delete map[x][y][z][k];
                }
                map[x][y][z].clear();
            }
            map[x][y].clear();
        }
        map[x].clear();
    }
    map.clear();
}


void Tilemap::createEmptyMap(const int mapSizeX, const int mapSizeY, const int mapSizeZ)
{
    assert(mapSizeX > 0 && mapSizeY > 0 && mapSizeZ > 0);

    map.resize(
        mapSizeX, 
        std::vector<std::vector<std::vector<Tile*>>>(
            mapSizeY, 
            std::vector<std::vector<Tile*>>(
                mapSizeZ, 
                std::vector<Tile*>(0)
            )
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


void Tilemap::updateTiles(Entity& entity, const float deltaTime)
{
    // Calculating the update bounds
    int z = 0;

    int fromX = entity.getGridPosition().x - 1;
    if (fromX < 0)
    {
        fromX = 0;
    }

    int toX = entity.getGridPosition().x + 3;
    if (toX > (int)map.size())
    {
        toX = map.size();
    }

    int fromY = entity.getGridPosition().y - 1;
    if (fromY < 0)
    {
        fromY = 0;
    }

    int toY = entity.getGridPosition().y + 3;
    if (toY > (int)map[0].size())
    {
        toY = map[0].size();
    }
    

    for (int x = fromX; x < toX; ++x)
    {
        for (int y = fromY; y < toY; ++y)
        {
            for (int k = 0; k < (int)map[x][y][z].size(); ++k)
            {
                map[x][y][z][k]->update();

                // Checking for the intersection
                if (map[x][y][z][k]->tileCanCollide() &&
                    map[x][y][z][k]->intersects(entity.getNextPositionBounds(deltaTime))
                   )
                {
                    handleCollision(*map[x][y][z][k], entity);
                }
            }
        }
    }
}


void Tilemap::handleCollision(const Tile& tile, Entity& entity)
{
    sf::FloatRect entityBounds       = entity.getGlobalBounds();
    sf::FloatRect tileBounds         = tile.getGlobalBounds();

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