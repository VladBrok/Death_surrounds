#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"


class Weapon: public Item
{
public:

                       Weapon(sf::Texture& texture, const int damage, const int damageMax);
    virtual            ~Weapon();
    virtual void       update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView) = 0;
    virtual void       render(sf::RenderTarget& target) = 0;

    float              getRange() const;
    virtual Weapon*    getClone() = 0;
                       
protected:             

    int                damage;
    int                damageMax;
    float              range;
};                     


#endif // WEAPON_H
