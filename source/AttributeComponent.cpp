#include "precompiled.h"
#include "AttributeComponent.h"


AttributeComponent::AttributeComponent(const unsigned level)
    : level(level),
      exp(0),
      expForNextLevel(46),
      attributePoints(3),
      vitality(1),
      strength(1),
      dexterity(1),
      agility(1),
      intelligence(1)
{
    updateStats(true);
}


void AttributeComponent::updateLevel()
{
    // Updating the level depending on the experience
    while (exp >= expForNextLevel)
    {
        ++level;
        ++attributePoints;
        exp -= expForNextLevel;
        expForNextLevel = static_cast<unsigned>(
            (50 / 3) * (std::pow((double)level, 3) - 6 * std::pow((double)level, 2) + level * 17 - 12)
        );
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



/*=============== Debug ===============*/

void AttributeComponent::debugPrint() const
{
    std::cout << "Level:                   " << level
              << "\nExp:                     " << exp
              << "\nExp for the  next level: " << expForNextLevel
              << "\nAttribute points:        " << attributePoints; 
}