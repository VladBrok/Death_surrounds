#include "precompiled.h"
#include "Tile.h"
#include "constants.h"


const std::string Tile::strTypes[NUMBER_OF_TILE_TYPES] = 
{
    "Default",
    "Rendering_deferred"
};


Tile::Tile(const float posX, 
           const float posY, 
           const sf::Texture& textureSheet, 
           const sf::IntRect& textureRect,
           const bool canCollide,
           const TileType type
           )
    : textureRect(textureRect), canCollide(canCollide), type(type)
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


const sf::FloatRect Tile::getGlobalBounds() const
{
    return tile.getGlobalBounds();
}


const std::string Tile::getAsString() const
{
    std::stringstream data;

    data << textureRect.left << ' ' << textureRect.top << ' ';

    return data.str();
}


TileType Tile::getType() const
{
    return type;
}


const std::string& Tile::getTypeAsString(const TileType type)
{
    assert(type >= 0 && type < NUMBER_OF_TILE_TYPES);

    return strTypes[type];
}


bool Tile::tileCanCollide() const
{
    return canCollide;
}


bool Tile::intersects(const sf::FloatRect& bounds)
{
    return tile.getGlobalBounds().intersects(bounds);
}