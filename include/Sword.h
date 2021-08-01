#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"


class Sword: public Weapon
{
public:

                    Sword();
    virtual void    update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView);
    virtual void    render(sf::RenderTarget& target);
};


#endif // SWORD_H
