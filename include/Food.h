#ifndef FOOD_H
#define FOOD_H

#include "Item.h"


class Food: public Item
{
public:

                                 Food(const sf::Texture& texture, 
                                      const sf::IntRect& textureRect = sf::IntRect()
                                      );
    virtual                      ~Food() {};
    virtual void                 update(const sf::Vector2f& foodPosition, 
                                        const sf::Vector2f& mousePosView
                                        );
                                 
    virtual Food*                getClone();
    virtual const std::string    getName() const;
    int                          getRestoringHpAmount() const;
                                 
    virtual bool                 isFood() const;
                                 
private:                         
                                 
    int                          restoringHpAmount;
    static const std::string     foodNames[];
                                 
    virtual void                 initDefaultOriginAndScale();
};


#endif // FOOD_H
