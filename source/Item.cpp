#include "precompiled.h"
#include "Item.h"


Item::Item(const sf::Texture& texture, const sf::IntRect& textureRect)
    : texture(texture), sprite(texture), defaultScale(1.f, 1.f) 
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


void Item::setOrigin(const float x, const float y)
{
    sprite.setOrigin(x, y);
}


void Item::setScale(const float factorX, const float factorY)
{
    sprite.setScale(factorX, factorY);
}


void Item::setRotation(const float angle)
{
    sprite.setRotation(angle);
}


bool Item::isWeapon() const
{
    return false;
}


bool Item::isFood() const
{
    return false;
}


const sf::Vector2f& Item::getPosition() const
{
    return sprite.getPosition();
}


const sf::IntRect& Item::getTextureRect() const
{
    return sprite.getTextureRect();
}


const sf::Vector2f& Item::getDefaultOrigin() const
{
    return defaultOrigin;
}


const sf::Vector2f& Item::getDefaultScale() const
{
    return defaultScale;
}


const sf::FloatRect Item::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}