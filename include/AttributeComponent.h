#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
public:

    // FIXME: decide which class attributes must be private!

    // Leveling
    unsigned     level;
    unsigned     exp;
    unsigned     expForNextLevel;
    unsigned     attributePoints;

    // Attributes
    int          vitality;
    int          strength;
    int          dexterity;
    int          agility;
    int          intelligence;

    // Stats
    int          hp;
    int          hpMax;
    int          damageMin;
    int          damageMax;
    int          accuracy;
    int          defence;
    int          luck;


                 AttributeComponent(const unsigned level);
    void         updateLevel();
    void         updateStats(bool resetHp = false);
    void         gainExp(const unsigned exp);
    void         loseHP(const unsigned points);
    void         gainHP(const unsigned points);

    // Debug
    void         debugPrint() const;
};


#endif // ATTRIBUTECOMPONENT_H
