#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
public:

    // FIXME: decide which class attributes must be private!

    unsigned    level;
    int         exp;
    int         expForNextLevel;
    int         hp;
    int         hpMax;
    int         damageMin;
    int         damageMax;


                AttributeComponent(const unsigned level, 
                                   const int hpMax, 
                                   const int damageMin, 
                                   const int damageMax
                                   );
    void        updateLevel();
    void        updateStats(bool resetHp = false);

    void        loseHp(const unsigned hp);
    void        gainHp(const unsigned hp);
    void        loseExp(const unsigned exp);
    void        gainExp(const unsigned exp);

    int         getDamage() const;

    // Debug
    void        debugPrint() const;

private:


};


#endif // ATTRIBUTECOMPONENT_H
