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
    // Updating the level and stats depending on the experience
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
    if (level % 3 == 0)
    {
        damageMin += 1;
        damageMax += 1;
    }

    if (level % 2 == 0)
    {
        hpMax += 1;
    }
}


void AttributeComponent::loseHp(const unsigned hp)
{
    this->hp = std::max(this->hp - hp, 0u);
}


void AttributeComponent::gainHp(const unsigned hp)
{
    this->hp = std::min(this->hp + (int)hp, hpMax);
}


void AttributeComponent::loseExp(const unsigned exp)
{
    this->exp = std::max(this->exp - exp, 0u);

    updateLevel();
}


void AttributeComponent::gainExp(const unsigned exp)
{
    this->exp += exp;

    updateLevel();
}


unsigned AttributeComponent::getLevel() const
{
    return level;
}


int AttributeComponent::getExp() const
{
    return exp;
}


int AttributeComponent::getExpForNextLevel() const
{
    return expForNextLevel;
}


int AttributeComponent::getHp() const
{
    return hp;
}


int AttributeComponent::getHpMax() const
{
    return hpMax;
}


int AttributeComponent::getDamageMin() const
{
    return damageMin;
}


int AttributeComponent::getDamageMax() const
{
    return damageMax;
}


int AttributeComponent::getDamage() const
{
    return rand() % (damageMax - damageMin + 1) + damageMin;
}
