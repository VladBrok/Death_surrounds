#include "precompiled.h"
#include "Food.h"


Food::Food(const sf::Texture& texture, const sf::IntRect& textureRect)
    : Item(texture, textureRect)
{
    restoringHpAmount = textureRect.left + 1;

    initDefaultOriginAndScale();

    sprite.setOrigin(defaultOrigin);
}


void Food::update(const sf::Vector2f& foodPosition, const sf::Vector2f& mousePosView)
{
    sprite.setPosition(foodPosition);
}


Food* Food::getClone()
{
    return new Food(*this);
}


int Food::getRestoringHpAmount() const
{
    return restoringHpAmount;
}


bool Food::isFood() const
{
    return true;
}


void Food::initDefaultOriginAndScale()
{
    defaultOrigin.x = sprite.getTextureRect().left + sprite.getTextureRect().width / 2.f;
    defaultOrigin.y = sprite.getTextureRect().top + sprite.getTextureRect().height / 2.f;

    defaultScale.x = defaultScale.y = 1.f;
}
