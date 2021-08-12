#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"


class Sword: public Weapon
{
public:
                      
                                 Sword(const sf::Texture& texture, 
                                       const int damage,
                                       const int damageMax, 
                                       const sf::IntRect& textureRect = sf::IntRect()
                                       );
    virtual void                 update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView);
    virtual Sword*               getClone();
    virtual const std::string    getName() const;
                      
private:              
                      
    virtual void                 initRange();
    virtual void                 initAttackTimerMax();
    virtual void                 initDefaultOriginAndScale();
};


#endif // SWORD_H
