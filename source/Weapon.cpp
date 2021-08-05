#include "precompiled.h"
#include "Weapon.h"


Weapon::Weapon(sf::Texture& texture, const int damage, const int damageMax)
    : Item(texture),
      damage(damage),
      damageMax(damageMax),
      range(0)
{
    attackTimer.restart();
}


Weapon::~Weapon()
{
}


bool Weapon::canAttack()
{
    if (attackTimer.getElapsedTime().asMilliseconds() >= attackTimerMax)
    {
        attackTimer.restart();
        return true;
    }
    return false;
}


int Weapon::getDamage() const
{
    return damage;
}


int Weapon::getDamageMax() const
{
    return damageMax;
}


float Weapon::getRange() const
{
    return range;
}
