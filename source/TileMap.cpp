#include "precompiled.h"
#include "TileMap.h"
#include "constants.h"


TileMap::TileMap(const int mapSizeX, const int mapSizeY, const int mapSizeZ)
{
    assert(mapSizeX > 0 && mapSizeY > 0 && mapSizeZ > 0);

    map.resize(
        mapSizeX, 
        std::vector<std::vector<Tile*>>(
            mapSizeY, std::vector<Tile*>(
                mapSizeZ, nullptr
            )
        )
    );

    textureSheet.loadFromFile("Resources\\Images\\Tiles\\tilesheet.png");
}


TileMap::~TileMap()
{
    clear();
}


void TileMap::clear()
{
    for (size_t x = 0; x < map.size(); ++x)
    {
        for (size_t y = 0; y < map[x].size(); ++y)
        {
            for (size_t z = 0; z < map[x][y].size(); ++z)
            {
                delete map[x][y][z];
                map[x][y][z] = nullptr;
            }
        }
    }
}


void TileMap::saveToFile(const std::string& fileName)
{
    /*
        Saving format:
            Map:
                1) map size               - x y z.

            All tiles:
                1) tile grid position     - gridPosX gridPosY;
                2) tile texture rectangle - x y.
    */

    std::ofstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        std::cout << "ERROR in TileMap::saveToFile: unable to save the tile map to the file " << fileName << '\n';
        return;
    }

    file << map.size() << ' ' << map[0].size() << ' ' << map[0][0].size() << '\n';

    for (size_t x = 0; x < map.size(); ++x)
    {
        for (size_t y = 0; y < map[x].size(); ++y)
        {
            for (size_t z = 0; z < map[x][y].size(); ++z)
            {
                if (map[x][y][z] != nullptr)
                {
                    file << map[x][y][z]->getAsString();
                }
            }
        }
    } 
}


void TileMap::loadFromFile(const std::string& fileName)
{
    /*
        The loading format is the same as the saving format.
    */

    std::ifstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        std::cout << "ERROR in TileMap::loadFromFile: unable to load the tile map from the file " << fileName << '\n';
        return;
    }


    int mapSizeX = 0;
    int mapSizeY = 0;
    int mapSizeZ = 0;

    file >> mapSizeX >> mapSizeY >> mapSizeZ;

    if (!file.fail() && mapSizeX > 0 && mapSizeY > 0 && mapSizeZ > 0)
    {
         clear();
    }


    int gridPosX = 0;
    int gridPosY = 0;
    sf::IntRect textureRect(0, 0, (int)GRID_SIZE, (int)GRID_SIZE);
    
    while (file >> gridPosX >> gridPosY >> textureRect.left >> textureRect.top)
    {
        map[gridPosX][gridPosY][0] = new Tile(
                                            gridPosX * GRID_SIZE, 
                                            gridPosY * GRID_SIZE, 
                                            textureSheet,
                                            textureRect
                                         );
    }

    if (file.fail() || mapSizeX <= 0 || mapSizeY <= 0 || mapSizeZ <= 0)
    {
        std::cout << "ERROR in TileMap::loadFromFile: the data in the file " << fileName << " are damaged. Tilemap is not loaded.\n";
    } 
}


void TileMap::addTile(const int gridPosX, const int gridPosY, const int gridPosZ, const sf::IntRect& textureRect)
{
    if (positionsAreCorrect(gridPosX, gridPosY, gridPosZ) &&
        map[gridPosX][gridPosY][gridPosZ] == nullptr)
    {
        map[gridPosX][gridPosY][gridPosZ] = new Tile(
                                                 gridPosX * GRID_SIZE, 
                                                 gridPosY * GRID_SIZE, 
                                                 textureSheet,
                                                 textureRect
                                                );
    }
}


void TileMap::removeTile(const int gridPosX, const int gridPosY, const int gridPosZ)
{
    if (positionsAreCorrect(gridPosX, gridPosY, gridPosZ) &&
        map[gridPosX][gridPosY][gridPosZ] != nullptr)
    {
        delete map[gridPosX][gridPosY][gridPosZ];
        map[gridPosX][gridPosY][gridPosZ] = nullptr;
    }
}


void TileMap::render(sf::RenderTarget& target)
{
    for (size_t x = 0; x < map.size(); ++x)
    {
        for (size_t y = 0; y < map[x].size(); ++y)
        {
            for (size_t z = 0; z < map[x][y].size(); ++z)
            {
                if (map[x][y][z] != nullptr)
                {
                    map[x][y][z]->render(target);
                }
            }
        }
    }
}


bool TileMap::positionsAreCorrect(const int gridPosX, const int gridPosY, const int gridPosZ) const
{
    return gridPosX >= 0 && gridPosX < (int)map.size() &&
           gridPosY >= 0 && gridPosY < (int)map[gridPosX].size() &&
           gridPosZ >= 0 && gridPosZ < (int)map[gridPosX][gridPosY].size();
}


const sf::Texture& TileMap::getTextureSheet() const
{
    return textureSheet;
}