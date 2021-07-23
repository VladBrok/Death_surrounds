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

    textureSheet.loadFromFile("Images\\Tiles\\tilesheet.png");
}


TileMap::~TileMap()
{
    for (size_t x = 0; x < map.size(); ++x)
    {
        for (size_t y = 0; y < map[x].size(); ++y)
        {
            for (size_t z = 0; z < map[x][y].size(); ++z)
            {
                delete map[x][y][z];
            }
        }
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