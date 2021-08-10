#include "precompiled.h"
#include "Food.h"


Food::Food(const sf::Texture& texture, const sf::IntRect& textureRect)
    : Item(texture, textureRect)
{
    restoringHpAmount = textureRect.left + 1;
}


void Food::update(const sf::Vector2f& foodPosition, const sf::Vector2f& mousePosView)
{
    //std::cout << "HI from food update!\n";
}


Food* Food::getClone()
{
    return new Food(*this);
}


int Food::getRestoringHpAmount() const
{
    return restoringHpAmount;
}
