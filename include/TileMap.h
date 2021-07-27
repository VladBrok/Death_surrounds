#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entity.h"


class Tilemap
{
public:

                            Tilemap(const int mapSizeX, const int mapSizeY, const int mapSizeZ);
                            ~Tilemap();

    void                    saveToFile(const std::string& fileName);
    void                    loadFromFile(const std::string& fileName);

    void                    addTile(const int gridPosX, 
                                    const int gridPosY, 
                                    const int gridPosZ, 
                                    const sf::IntRect& textureRect,
                                    const bool canCollide
                                    );
    void                    removeTile(const int gridPosX, const int gridPosY, const int gridPosZ);
    void                    render(sf::RenderTarget& target, 
                                   const sf::Vector2i& gridPositionAroundWhichRender
                                   );
    void                    updateCollision(Entity& entity, const float deltaTime);

    const sf::Texture&      getTextureSheet() const;
    int                     getNumberOfTilesAtPosition(const sf::Vector2i& gridPosition, const int layer);

private:

    std::vector< std::vector< std::vector< std::vector< Tile* > > > > map;
    sf::Texture                                        textureSheet;
    sf::RectangleShape                                 collisionBox;
    sf::Vector3f                                       mapGridSize;

    bool positionsAreCorrect(const int gridPosX, const int gridPosY, const int gridPosZ) const;
    void clearMap();
    void createEmptyMap(const int mapSizeX, const int mapSizeY, const int mapSizeZ);

    void updateCollisionWithMapBounds(Entity& entity, const float deltaTime);
    void updateCollisionWithTiles(Entity& entity, const float deltaTime);
    void handleCollision(const Tile& tile, Entity& entity);
};


#endif // TILEMAP_H
