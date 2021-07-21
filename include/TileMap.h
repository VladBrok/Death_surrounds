#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"


const float GRID_SIZE = 50.f;


class TileMap
{
public:

    TileMap(const int mapSizeX, const int mapSizeY, const int mapSizeZ);

    void render(sf::RenderTarget& target);

private:

    std::vector< std::vector< std::vector< Tile > > > map;

};


#endif // TILEMAP_H
