#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entity.h"


class Tilemap
{
public:

                            Tilemap(const int mapSizeX, const int mapSizeY, const int mapSizeZ);
                            Tilemap(const std::string& fileName);
                            ~Tilemap();

    void                    update(Entity& entity, const float deltaTime);
    void                    render(sf::RenderTarget& target, 
                                   const sf::Vector2i& gridPositionAroundWhichRender,
                                   sf::Shader* pShader = nullptr,
                                   const sf::Vector2f& shaderLightPosition = sf::Vector2f(),
                                   const bool showCollisionBox = false
                                   );
    void                    renderDeferred(sf::RenderTarget& target,
                                           sf::Shader* pShader = nullptr,
                                           const sf::Vector2f& shaderLightPosition = sf::Vector2f()                                         
                                           );

    void                    saveToFile(const std::string& fileName);
    void                    loadFromFile(const std::string& fileName);
    void                    addTile(const int gridPosX, 
                                    const int gridPosY, 
                                    const int gridPosZ, 
                                    const sf::IntRect& textureRect,
                                    const bool canCollide,
                                    const TileType type
                                    );
    void                    removeTile(const int gridPosX, const int gridPosY, const int gridPosZ);


    const sf::Texture&      getTextureSheet() const;
    int                     getNumberOfTilesAtPosition(const sf::Vector2i& gridPosition, const int layer);
    const std::string&      getTileTypeAsString(const int type);
    const sf::Vector3f&     getMapSize() const;

private:

    std::vector< std::vector< std::vector< std::vector< Tile* > > > > map;
    sf::Vector3f                                                      mapSize;
    sf::Texture                                                       textureSheet;
    std::string                                                       textureSheetFileName;
    sf::RectangleShape                                                collisionBox;
    std::stack<Tile*>                                                 tilesForDeferredRender;

    bool                    positionsAreCorrect(const int gridPosX, const int gridPosY, const int gridPosZ) const;
    void                    clearMap();
    void                    createEmptyMap(const int mapSizeX, const int mapSizeY, const int mapSizeZ);
                            
    void                    updateCollisionWithMapBounds(Entity& entity, const float deltaTime);
    void                    updateTiles(Entity& entity, const float deltaTime);
    void                    handleCollision(const Tile& tile, Entity& entity);

    void                    initCollisionBox();
};


#endif // TILEMAP_H
