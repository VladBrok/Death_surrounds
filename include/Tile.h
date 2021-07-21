#ifndef TILE_H
#define TILE_H


class Tile
{
public:

    Tile(const float posX, const float posY, const float gridSize);
    virtual ~Tile();

    void render(sf::RenderTarget& target);

private:

    sf::RectangleShape tile;
};


#endif // TILE_H
