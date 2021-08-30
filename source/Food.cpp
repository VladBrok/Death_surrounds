#include "precompiled.h"
#include "Food.h"
#include "constants.h"


const std::string Food::foodNames[] =
{
    "Apple",
    "Rasberry",
    "Banana",
    "Cake",
    "Grape",
    "Cheese",
    "Meat",
    "Fish",
    "Bread",
    "Beer"
};


Food::Food(const sf::Texture& texture, const sf::IntRect& textureRect)
    : Item(texture, textureRect)
{
    restoringHpAmount = ((int)textureRect.left / ONE_FOOD_TEXTURE_SIZE) + 1;

    initDefaultOriginAndScale();

    sprite.setOrigin(defaultOrigin);
}


void Food::update(const sf::Vector2f& foodPosition, const sf::Vector2f&)
{
    sprite.setPosition(foodPosition);
}


std::unique_ptr<Item> Food::getClone()
{
    std::unique_ptr<Food> clone(new Food(*this));
    return std::move(clone);
}


const std::string Food::getName() const
{
    return foodNames[restoringHpAmount - 1];
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
