#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
class Entity;


enum WeaponType
{
    MELEE_WEAPON,
    RANGED_WEAPON
};


class Weapon: public Item
{
public:
                    
                          Weapon(const sf::Texture& texture, 
                                 const int damageMin, 
                                 const int damageMax, 
                                 const sf::IntRect& textureRect = sf::IntRect()
                                 );
    virtual               ~Weapon() {};
    virtual void          update(const sf::Vector2f& weaponPosition,
                                 const sf::Vector2f& mousePosView) = 0;
                          
    bool                  canAttack();
    void                  restartAttackTimer();
    virtual bool          isWeapon() const;
                          
    int                   getDamage() const;
    int                   getDamageMin() const;
    int                   getDamageMax() const;
    float                 getRange() const;
    virtual WeaponType    getWeaponType() const = 0;
                    
protected:          
                    
    int                   damageMin;
    int                   damageMax;
    float                 range;
    sf::Clock             attackTimer;
    sf::Int32             attackTimerMax;
                          
    virtual void          initRange() = 0;
    virtual void          initAttackTimerMax() = 0;
};                     


#endif // WEAPON_H
