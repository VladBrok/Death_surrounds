#include "precompiled.h"
#include "Weapon.h"


Weapon::Weapon(sf::Texture& texture, const int damage, const int damageMax)
    : Item(texture),
      damage(damage),
      damageMax(damageMax),
      range(0)
{
}


Weapon::~Weapon()
{
}


float Weapon::getRange() const
{
    return range;
}