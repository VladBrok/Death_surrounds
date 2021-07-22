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

    // TEST
    for (size_t x = 0; x < map.size(); ++x)
    {
        for (size_t y = 0; y < map[x].size(); ++y)
        {
            for (size_t z = 0; z < map[x][y].size(); ++z)
            {
                map[x][y][z] = new Tile(x * GRID_SIZE, y * GRID_SIZE);
            }
        }
    }
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


void TileMap::render(sf::RenderTarget& target)
{
    for (size_t x = 0; x < map.size(); ++x)
    {
        for (size_t y = 0; y < map[x].size(); ++y)
        {
            for (size_t z = 0; z < map[x][y].size(); ++z)
            {
                map[x][y][z]->render(target);
            }
        }
    }
}