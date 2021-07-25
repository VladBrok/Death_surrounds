#include "precompiled.h"
#include "Tile.h"
#include "constants.h"


Tile::Tile(const float posX, 
           const float posY, 
           const sf::Texture& textureSheet, 
           const sf::IntRect& textureRect,
           const bool canCollide
           )
    : textureRect(textureRect), canCollide(canCollide)
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


const sf::Vector2f& Tile::getPosition() const
{
    return tile.getPosition();
}


const std::string Tile::getAsString() const
{
    std::stringstream data;

    data << textureRect.left << ' ' << textureRect.top << ' ';

    return data.str();
}


bool Tile::tileCanCollide() const
{
    return canCollide;
}