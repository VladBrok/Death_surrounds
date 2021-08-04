#include "precompiled.h"
#include "Item.h"


Item::Item(sf::Texture& texture)
    : texture(texture), sprite(texture)
{
}


Item::~Item()
{
}