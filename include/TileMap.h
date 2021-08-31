#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
class Entity;
class EnemySystem;


class Tilemap
{
public:

                           Tilemap(const int mapGridSizeX, const int mapGridSizeY);
    explicit               Tilemap(const std::string& fileName);
                           
    void                   update(Entity& entity,
                                  const float deltaTime, 
                                  EnemySystem& enemySystem
                                  );
    void                   render(sf::RenderTarget& target, 
                                  const sf::View& view,
                                  const sf::Vector2i& gridPositionAroundWhichRender = sf::Vector2i(-1, -1),
                                  sf::Shader* pShader = nullptr,
                                  const sf::Vector2f& shaderLightPosition = sf::Vector2f(),
                                  const bool showCollisionBox = false,
                                  const bool showEnemySpawnerBox = false
                                  );
    void                   renderDeferred(sf::RenderTarget& target,
                                          sf::Shader* pShader = nullptr,
                                          const sf::Vector2f& shaderLightPosition = sf::Vector2f()                                         
                                          );
    void                   saveToFile(const std::string& fileName);
    void                   loadFromFile(const std::string& fileName);
    void                   addTile(const int gridPosX, 
                                   const int gridPosY, 
                                   const sf::IntRect& textureRect,
                                   const bool canCollide,
                                   const TileType type
                                   );
    void                   addEnemySpawnerTile(const int gridPosX,
                                               const int gridPosY,
                                               const sf::IntRect& textureRect,
                                               const bool canCollide,
                                               const int enemyType,
                                               const int enemyTimeToSpawn
                                               );
    void                   removeTile(const int gridPosX, const int gridPosY);
                           
    const sf::Texture&     getTextureSheet() const;
    int                    getNumberOfTilesAtPosition(const sf::Vector2i& gridPosition);
    int                    getTileType(const int gridPosX, const int gridPosY);
    const std::string&     getTileTypeAsString(const int type);
    const sf::Vector2f&    getMapSize() const;

private:
    typedef std::vector< std::vector< std::vector< std::unique_ptr<Tile> > > > TilemapContainer;


    TilemapContainer       map;
    sf::Vector2f           mapSize;
    sf::Texture            textureSheet;
    std::string            textureSheetFileName;
                           
    sf::RectangleShape     collisionBox;
    sf::RectangleShape     enemySpawnerBox;
                             
    std::stack<Tile*>      tilesForDeferredRender;
                           
    bool                   positionsAreCorrect(const int gridPosX, const int gridPosY) const;
    void                   createEmptyMap(const int mapSizeX, const int mapSizeY);
                           
    void                   updateCollisionWithMapBounds(Entity& entity, const float deltaTime);
    void                   updateTiles(Entity& entity, 
                                       const float deltaTime,
                                       EnemySystem& enemySystem
                                       );
                           
    void                   handleCollision(const Tile& tile, Entity& entity);
    void                   renderTile(sf::RenderTarget& target, 
                                      Tile& tile,
                                      sf::Shader* pShader = nullptr,
                                      const sf::Vector2f& shaderLightPosition = sf::Vector2f(),
                                      const bool showCollisionBox = false,
                                      const bool showEnemySpawnerBox = false
                                      );
                           
    void                   initCollisionBox();
    void                   initEnemySpawnerBox();
};


#endif // TILEMAP_H
