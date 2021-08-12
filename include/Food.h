#ifndef FOOD_H
#define FOOD_H

#include "Item.h"


class Food: public Item
{
public:

                                  Food(const sf::Texture& texture, const sf::IntRect& textureRect = sf::IntRect());
    virtual                       ~Food() {};
    virtual void                  update(const sf::Vector2f& foodPosition, const sf::Vector2f& mousePosView);
                                  
    virtual Food*                 getClone();
    int                           getRestoringHpAmount() const;

    virtual bool                  isFood() const;

private:

    int                           restoringHpAmount;

    virtual void                  initDefaultOriginAndScale();
};


#endif // FOOD_H
