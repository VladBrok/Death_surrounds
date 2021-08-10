#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Sword.h"
#include "Inventory.h"


class Player: public Entity
{
public:
    
                         Player(const float posX, 
                                const float posY, 
                                sf::Texture& textureSheet
                                );
    virtual void         update(const float deltaTime, const sf::Vector2f& mousePosView);
    virtual void         render(sf::RenderTarget& target, 
                                sf::Shader* pShader = nullptr,
                                const sf::Vector2f& shaderLightPosition = sf::Vector2f(),
                                const bool showHitbox = false
                                );

    bool                 addItemToInventory(Item*, const bool isWeapon = false, const bool setAsActive = false);
                         
    int                  getHP() const;
    int                  getHPMax() const;
    int                  getExp() const;
    int                  getExpForNextLevel() const;
    unsigned             getLevel() const;
    int                  getDamage() const;
    float                getAttackRange() const;
    const std::string    getStatsAsString() const;
    int                  getNumberOfItems() const;

    void                 loseHp(const unsigned hp);
    void                 gainHp(const unsigned hp);
    void                 loseExp(const unsigned exp);
    void                 gainExp(const unsigned exp);
                         
    void                 setAttackStatus(const bool attacking);
    bool                 isAttacking() const;
    bool                 canBeDamaged() const;
    void                 restartDamageTimer();
    bool                 canAttack() const;
    bool                 isDead() const;
                         
private:                 
                         
    Inventory            inventory;
    Weapon*              pActiveWeapon;
    bool                 attacking;
    sf::Clock            damageTimer;
    sf::Int32            damageTimerMax;
                         
    void                 updateAnimation(const float deltaTime);
    void                 updateInventory(const sf::Vector2f& mousePosView);
    void                 renderInventory(sf::RenderTarget& target);
                         
    void                 initDamageTimerMax();
};


#endif // PLAYER_H
