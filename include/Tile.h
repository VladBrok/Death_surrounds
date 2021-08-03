#ifndef TILE_H
#define TILE_H


enum TileType
{
    DEFAULT,
    RENDERING_DEFERRED,
    ENEMY_SPAWNER,
    NUMBER_OF_TILE_TYPES
};


class Tile
{
public:

                                      Tile(const TileType type,
                                           const float posX, 
                                           const float posY, 
                                           const sf::Texture& textureSheet, 
                                           const sf::IntRect& textureRect,
                                           const bool canCollide
                                           );
    virtual                           ~Tile();
    
    virtual void                      update();          
    virtual void                      render(sf::RenderTarget& target,
                                             sf::Shader* pShader = nullptr,
                                             const sf::Vector2f& shaderLightPosition = sf::Vector2f()
                                             );

    // Returns string with the texture rectangle position and tile collision ability (canCollide)
    virtual const std::string          getAsString() const; 
                                       
    const sf::Vector2f&                getPosition() const;
    const sf::FloatRect                getGlobalBounds() const;
    TileType                           getType() const;
    static const std::string&          getTypeAsString(const TileType type);
    const sf::IntRect&                 getTextureRect() const;

    bool                               tileCanCollide() const;
    bool                               intersects(const sf::FloatRect& bounds);
                               
protected:                       
                               
    sf::Sprite                         tile;
    sf::IntRect                        textureRect;
    TileType                           type;
    bool                               canCollide;
    static const std::string           strTypes[NUMBER_OF_TILE_TYPES];
};


#endif // TILE_H
