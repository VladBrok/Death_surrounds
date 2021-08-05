#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"


class Enemy: public Entity
{
public:

                          Enemy(const float posX, const float posY, const sf::Texture& textureSheet);
    virtual void          update(const float deltaTime, const sf::Vector2f& mousePosView) = 0;
    void                  loseHp(const unsigned hp);
    bool                  isDead() const;

    // Returns the amount of experience that you will get after killing this enemy
    unsigned              getExpForKilling() const;

protected:

    unsigned              level;
    unsigned              expForKillingMax;  

    virtual void          initAnimation() = 0;
    virtual void          updateAnimation(const float deltaTime) = 0;
};


#endif // ENEMY_H
