#include "precompiled.h"
#include "Food.h"
#include "constants.h"


Food::Food(const sf::Texture& texture, const sf::IntRect& textureRect)
    : Item(texture, textureRect)
{
    restoringHpAmount = ((int)textureRect.left / ONE_FOOD_TEXTURE_SIZE) + 1;

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
    defaultOrigin.x = defaultOrigin.y = (float)(ONE_FOOD_TEXTURE_SIZE / 2);

    defaultScale.x = defaultScale.y = 1.f;
}