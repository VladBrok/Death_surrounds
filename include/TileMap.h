#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"


class TileMap
{
public:

                            TileMap(const int mapSizeX, const int mapSizeY, const int mapSizeZ);
                            ~TileMap();

    void                    addTile(const int gridPosX, const int gridPosY, const int gridPosZ, const sf::IntRect& textureRect);
    void                    removeTile(const int gridPosX, const int gridPosY, const int gridPosZ);
    void                    render(sf::RenderTarget& target);
    const sf::Texture&      getTextureSheet() const;

private:

    std::vector< std::vector< std::vector< Tile* > > > map;
    sf::Texture                                        textureSheet;

    bool positionsAreCorrect(const int gridPosX, const int gridPosY, const int gridPosZ) const;

};


#endif // TILEMAP_H
