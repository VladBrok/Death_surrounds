#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
public:

    // FIXME: decide which class attributes must be private!

    // Leveling
    unsigned     level;
    int          exp;
    int          expForNextLevel;
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
    void         loseHp(const unsigned hp);
    void         gainHp(const unsigned hp);
    void         loseExp(const unsigned exp);
    void         gainExp(const unsigned exp);

    // Debug
    void         debugPrint() const;
};


#endif // ATTRIBUTECOMPONENT_H
