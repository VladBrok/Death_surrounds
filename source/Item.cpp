#include "precompiled.h"
#include "Item.h"


Item::Item(const sf::Texture& texture, const sf::IntRect& textureRect)
    : texture(texture), sprite(texture)
{
    if (textureRect != sf::IntRect())
    {
        sprite.setTextureRect(textureRect);
    }
}


void Item::render(sf::RenderTarget& target)
{
    target.draw(sprite);
}


void Item::setPosition(const float x, const float y)
{
    sprite.setPosition(x, y);
}


const sf::FloatRect Item::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}