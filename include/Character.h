#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"


class Character: public Entity
{
public:

    explicit        Character(const sf::Texture& texture);

    virtual void    gainHp(const int hp);
    virtual void    loseHp(const int hp);
    bool            isDead() const;
    virtual int     getDamage() const;

    // The damage timer should be restarted manually if needed, using the "restartDamageTimer" method
    bool            canBeDamaged() const;
    void            restartDamageTimer();
                    
    // The attack timer should be restarted manually if needed, using the "restartAttackTimer" method
    virtual bool    canAttack() const;
    void            restartAttackTimer();

protected:

    sf::Clock       damageTimer;
    sf::Int32       damageTimerMax;
                    
    sf::Clock       attackTimer;
    sf::Int32       attackTimerMax;

    // Sets the color of the sprite to red if character is taking damage
    void            updateDamageColor();
                    
    virtual void    updateAnimation(const float deltaTime);
    virtual void    initTimers() = 0;

private:

    bool            justSpawned;
};


#endif // CHARACTER_H
