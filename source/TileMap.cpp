#include "precompiled.h"
#include "TileMap.h"


TileMap::TileMap(const int mapSizeX, const int mapSizeY, const int mapSizeZ)
{
    assert(mapSizeX > 0 && mapSizeY > 0 && mapSizeZ > 0);

    // This is genious but i have to refuse it... because of a TILE POSITION!!!!!
    //map.resize(
    //    mapSizeX, 
    //    std::vector<std::vector<Tile>>(
    //        mapSizeY, std::vector<Tile>(
    //            mapSizeZ, Tile(GRID_SIZE)
    //        )
    //    )
    //);

    map.resize(mapSizeX);
    for (size_t x = 0; x < map.size(); ++x)
    {
        map[x].resize(mapSizeY);
        for (size_t y = 0; y < map[x].size(); ++y)
        {
            map[x][y].reserve(mapSizeZ);
            for (size_t z = 0; z < mapSizeZ; ++z)
            {
                map[x][y].push_back(Tile(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE));
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
                map[x][y][z].render(target);
            }
        }
    }
}