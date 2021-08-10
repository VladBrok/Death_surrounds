#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
class Item;


class Enemy: public Entity
{
public:

                             Enemy(const float posX, 
                                   const float posY, 
                                   const sf::Texture& textureSheet,
                                   const sf::Texture& lootTextureSheet
                                   );
    virtual void             update(const float deltaTime, const sf::Vector2f& mousePosView) = 0;
    void                     loseHp(const unsigned hp);
    bool                     isDead() const;
                             
    bool                     canBeDespawned(const sf::View& view) const;
    bool                     canBeDamaged() const;
    void                     restartDamageTimer();

    // Returns the amount of experience that you will get after killing this enemy
    unsigned                 getExpForKilling() const;
                             
    int                      getDamage() const;
    Item*                    getDroppingItem() const;
                             
protected:                   
              
    const sf::Texture&       lootTextureSheet;
    unsigned                 level;
    unsigned                 expForKillingMax;  
    sf::Clock                damageTimer;
    sf::Int32                damageTimerMax;
    std::shared_ptr<Item>    droppingItem;

    virtual void             updateAnimation(const float deltaTime) = 0;
    virtual void             initAnimation() = 0;
    void                     initDamageTimerMax();
    virtual void             initDroppingItem() = 0;
};


#endif // ENEMY_H
