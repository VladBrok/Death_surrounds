#include "precompiled.h"
#include "Weapon.h"


Weapon::Weapon(const sf::Texture& texture, 
               const int damageMin,
               const int damageMax,
               const sf::IntRect& textureRect
               )
    : Item(texture, textureRect),
      damageMin(damageMin),
      damageMax(damageMax),
      range(0)
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


void Weapon::restartAttackTimer()
{
    attackTimer.restart();
}


bool Weapon::isWeapon() const
{
    return true;
}


int Weapon::getDamage() const
{
    return rand() % (damageMax - damageMin + 1) + damageMin;
}


int Weapon::getDamageMin() const
{
    return damageMin;
}


int Weapon::getDamageMax() const
{
    return damageMax;
}


float Weapon::getRange() const
{
    return range;
}
