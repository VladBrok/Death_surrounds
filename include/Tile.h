#ifndef TILE_H
#define TILE_H


class Tile
{
public:

                            Tile(const float posX, 
                                 const float posY, 
                                 const sf::Texture& textureSheet, 
                                 const sf::IntRect& textureRect
                                 );
    virtual                 ~Tile();

    void                    render(sf::RenderTarget& target);

    // Returns string with the grid position and the texture rectangle position
    const std::string       getAsString() const; 

private:

    sf::RectangleShape      tile;
    sf::IntRect             textureRect;
};


#endif // TILE_H
