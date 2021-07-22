#include "precompiled.h"
#include "Tile.h"
#include "constants.h"


Tile::Tile(const float posX, const float posY)
{
    tile.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
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