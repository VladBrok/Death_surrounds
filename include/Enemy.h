#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
class Item;


class Enemy: public Character
{
public:

                             Enemy(const float posX, 
                                   const float posY, 
                                   const sf::Texture& textureSheet,
                                   const sf::Texture& lootTextureSheet
                                   );
    virtual void             update(const float deltaTime) = 0;                       
    bool                     canBeDespawned(const sf::View& view) const;

    // Returns the amount of experience that you will get after killing this enemy
    int                      getExpForKilling() const;
                             
    Item*                    getDroppingItem() const;
                             
protected:                   
              
    const sf::Texture&       lootTextureSheet;
    unsigned                 level;
    int                      expForKillingMax;
    std::shared_ptr<Item>    droppingItem;

    virtual void             updateAnimation(const float deltaTime) = 0;
    virtual void             initAnimation() = 0;
    virtual void             initTimers();
    virtual void             initDroppingItem() = 0;
};


#endif // ENEMY_H
