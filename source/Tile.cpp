#include "precompiled.h"
#include "Tile.h"
#include "constants.h"


const std::string Tile::STR_TYPES[NUMBER_OF_TILE_TYPES] = 
{
    "Default",
    "Rendering_deferred",
    "Enemy_spawner"
};


Tile::Tile(const TileType type,
           const float posX, 
           const float posY, 
           const sf::Texture& textureSheet, 
           const sf::IntRect& textureRect,
           const bool canCollide
           )
    : textureRect(textureRect), canCollide(canCollide), type(type)
{
    tile.setPosition(posX, posY);
    tile.setTexture(textureSheet, true);
    tile.setTextureRect(textureRect);

}


Tile::~Tile()
{
}


void Tile::render(sf::RenderTarget& target,
                  sf::Shader* pShader,
                  const sf::Vector2f& shaderLightPosition
                  )
{
    if (pShader)
    {
        pShader->setParameter("hasTexture", true);
        pShader->setParameter("light", shaderLightPosition);

        target.draw(tile, pShader);
    }
    else
    {
        target.draw(tile);
    }
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

    data << textureRect.left << ' ' << textureRect.top << ' ' << canCollide;

    return data.str();
}


TileType Tile::getType() const
{
    return type;
}


const std::string& Tile::getTypeAsString(const TileType type)
{
    assert(type >= 0 && type < NUMBER_OF_TILE_TYPES);

    return STR_TYPES[type];
}


const sf::IntRect& Tile::getTextureRect() const
{
    return textureRect;
}


void Tile::setPosition(const sf::Vector2f& position)
{
    tile.setPosition(position);
}


bool Tile::tileCanCollide() const
{
    return canCollide;
}


bool Tile::intersects(const sf::FloatRect& bounds)
{
    return tile.getGlobalBounds().intersects(bounds);
}