#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"


class Weapon: public Item
{
public:

                       Weapon(sf::Texture& texture, const int damageMin, const int damageMax);
    virtual            ~Weapon();
    virtual void       update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView) = 0;
    virtual void       render(sf::RenderTarget& target) = 0;

    bool               canAttack();

    int                getDamage() const;
    float              getRange() const;
    virtual Weapon*    getClone() = 0;
                       
protected:             

    int                damageMin;
    int                damageMax;
    float              range;
    sf::Clock          attackTimer;
    sf::Int32          attackTimerMax;

    virtual void       initRange() = 0;
    virtual void       initAttackTimerMax() = 0;
};                     


#endif // WEAPON_H
