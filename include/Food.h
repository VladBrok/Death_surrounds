#ifndef FOOD_H
#define FOOD_H

#include "Item.h"


class Food: public Item
{
public:

                           Food(const sf::Texture& texture, const sf::IntRect& textureRect = sf::IntRect());
    virtual                ~Food() {};
    virtual void           update(const sf::Vector2f& foodPosition, const sf::Vector2f& mousePosView);
                           
    virtual Food*          getClone();
    int                    getRestoringHpAmount() const;

private:

    int restoringHpAmount;
};


#endif // FOOD_H
