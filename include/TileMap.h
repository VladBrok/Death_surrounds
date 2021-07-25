#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"


class Tilemap
{
public:

                            Tilemap(const int mapSizeX, const int mapSizeY, const int mapSizeZ);
                            ~Tilemap();

    void                    saveToFile(const std::string& fileName);
    void                    loadFromFile(const std::string& fileName);

    void                    addTile(const int gridPosX, const int gridPosY, const int gridPosZ, const sf::IntRect& textureRect);
    void                    removeTile(const int gridPosX, const int gridPosY, const int gridPosZ);
    void                    render(sf::RenderTarget& target);

    const sf::Texture&      getTextureSheet() const;

private:

    std::vector< std::vector< std::vector< Tile* > > > map;
    sf::Texture                                        textureSheet;

    bool positionsAreCorrect(const int gridPosX, const int gridPosY, const int gridPosZ) const;

    void clearMap();
    void createEmptyMap(const int mapSizeX, const int mapSizeY, const int mapSizeZ);

};


#endif // TILEMAP_H
