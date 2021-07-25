#ifndef TILE_H
#define TILE_H


class Tile
{
public:

                            Tile(const float posX, 
                                 const float posY, 
                                 const sf::Texture& textureSheet, 
                                 const sf::IntRect& textureRect,
                                 const bool canCollide
                                 );
    virtual                 ~Tile();

    void                    render(sf::RenderTarget& target);

    // Returns string with the texture rectangle position
    const std::string       getAsString() const; 

    const sf::Vector2f&     getPosition() const;

    bool                    tileCanCollide() const;

private:

    sf::RectangleShape      tile;
    sf::IntRect             textureRect;
    bool                    canCollide;
};


#endif // TILE_H
