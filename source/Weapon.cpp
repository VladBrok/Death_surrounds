#include "precompiled.h"
#include "Weapon.h"


Weapon::Weapon(sf::Texture& texture, const int damageMin, const int damageMax)
    : Item(texture),
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
    else
    {
        return false;
    }
}

void Weapon::restartAttackTimer()
{
    attackTimer.restart();
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
