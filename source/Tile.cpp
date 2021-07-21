#include "precompiled.h"
#include "Tile.h"


Tile::Tile(const float posX, const float posY, const float gridSize)
{
    tile.setSize(sf::Vector2f(gridSize, gridSize));
    tile.setPosition(posX, posY);

    tile.setFillColor(sf::Color::Green);
    tile.setOutlineThickness(1.f);
    tile.setOutlineColor(sf::Color::White);
}


Tile::~Tile()
{
}


void Tile::render(sf::RenderTarget& target)
{
    target.draw(tile);
}