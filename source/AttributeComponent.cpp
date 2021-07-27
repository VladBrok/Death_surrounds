#include "precompiled.h"
#include "AttributeComponent.h"


AttributeComponent::AttributeComponent(const unsigned level)
    : level(level),
      exp(0),
      expForNextLevel(0),
      attributePoints(3),
      vitality(1),
      strength(1),
      dexterity(1),
      agility(1),
      intelligence(1)
{
    updateStats();
}


void AttributeComponent::updateLevel()
{
    // Updating the level depending on the experience
    while (exp >= expForNextLevel)
    {
        ++level;
        ++attributePoints;
        exp -= expForNextLevel;
        expForNextLevel = (50 / 3) * (std::pow((double)level, 3) - 6 * std::pow((double)level, 2) + level * 17 - 12);
    }
}


void AttributeComponent::updateStats(bool resetHp)
{
    // Updating the stats depending on the attributes
    hpMax       =    vitality * 6      + strength / 2   + intelligence / 5;
    damageMin   =    strength * 2      + strength / 4   + intelligence / 5;
    damageMax   =    strength * 2      + strength / 2   + intelligence / 5;
    accuracy    =    dexterity * 5     + dexterity / 2  + intelligence / 5;
    defence     =    agility * 2       + agility / 4    + intelligence / 5;
    luck        =    intelligence * 2                   + intelligence / 5;

    if (resetHp)
    {
        hp = hpMax;
    }
}


void AttributeComponent::update()
{
    updateLevel();
}