#include "precompiled.h"
#include "AttributeComponent.h"


AttributeComponent::AttributeComponent(const unsigned level, 
                                       const int hpMax, 
                                       const int damageMin, 
                                       const int damageMax
                                       )
                                       : level(level),
                                         exp(0),
                                         expForNextLevel(46),
                                         hpMax(hpMax),
                                         damageMin(damageMin),
                                         damageMax(damageMax)
{
    hp = hpMax;
}


void AttributeComponent::updateLevel()
{
    // Updating the level depending on the experience
    while (exp >= expForNextLevel)
    {
        ++level;

        updateStats();

        exp -= expForNextLevel;
        expForNextLevel = (int)((50 * std::powl(level, 3) - 150 * std::powl(level, 2) + 400 * level) / 3);
    }
}


void AttributeComponent::updateStats()
{
    if (level % 5 == 0)
    {
        hpMax += 1;
        damageMin += 1;
    }

    if (level % 3 == 0)
    {
        damageMax += 1;
    }
}


void AttributeComponent::loseHp(const unsigned hp)
{
    this->hp -= hp;
    
    if (this->hp < 0)
    {
        this->hp = 0;
    }
}


void AttributeComponent::gainHp(const unsigned hp)
{
    this->hp += hp;

    if (this->hp > hpMax)
    {
        this->hp = hpMax;
    }
}


void AttributeComponent::loseExp(const unsigned exp)
{
    this->exp -= exp;

    if (this->exp < 0)
    {
        this->exp = 0;
    }

    updateLevel();
}


void AttributeComponent::gainExp(const unsigned exp)
{
    this->exp += exp;

    updateLevel();
}


int AttributeComponent::getDamage() const
{
    return rand() % (damageMax - damageMin + 1) + damageMin;
}
