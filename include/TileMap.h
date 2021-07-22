#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"


class TileMap
{
public:

    TileMap(const int mapSizeX, const int mapSizeY, const int mapSizeZ);
    ~TileMap();

    void render(sf::RenderTarget& target);

private:

    std::vector< std::vector< std::vector< Tile* > > > map;

};


#endif // TILEMAP_H
