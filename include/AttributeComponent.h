#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
public:

                AttributeComponent(const unsigned level, 
                                   const int hpMax, 
                                   const int damageMin, 
                                   const int damageMax
                                   );
    void        updateLevel();
    void        updateStats();

    void        loseHp(const unsigned hp);
    void        gainHp(const unsigned hp);
    void        loseExp(const unsigned exp);
    void        gainExp(const unsigned exp);

    unsigned    getLevel() const;
    int         getExp() const;
    int         getExpForNextLevel() const;
    int         getHp() const;
    int         getHpMax() const;
    int         getDamageMin() const;
    int         getDamageMax() const;
    int         getDamage() const;

private:

    unsigned    level;
    int         exp;
    int         expForNextLevel;
    int         hp;
    int         hpMax;
    int         damageMin;
    int         damageMax;
};


#endif // ATTRIBUTECOMPONENT_H
