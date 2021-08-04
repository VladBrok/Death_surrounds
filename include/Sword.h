#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"


class Sword: public Weapon
{
public:

                    Sword(sf::Texture& texture, const int damage, const int damageMax);
    virtual void    update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView);
    virtual void    render(sf::RenderTarget& target);
    virtual Sword*  getClone();
};


#endif // SWORD_H
