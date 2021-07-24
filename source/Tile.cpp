#include "precompiled.h"
#include "Tile.h"
#include "constants.h"


Tile::Tile(const float posX, 
           const float posY, 
           const sf::Texture& textureSheet, 
           const sf::IntRect& textureRect
           )
    : textureRect(textureRect)
{
    tile.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    tile.setPosition(posX, posY);

    tile.setTexture(&textureSheet, true);
    tile.setTextureRect(textureRect);

}


Tile::~Tile()
{
}


void Tile::render(sf::RenderTarget& target)
{
    target.draw(tile);
}


const std::string Tile::getAsString() const
{
    std::stringstream data;

    data << (int)(tile.getPosition().x / GRID_SIZE) << ' ' << (int)(tile.getPosition().y / GRID_SIZE) << ' ';
    data << textureRect.left << ' ' << textureRect.top << ' ';

    return data.str();
}