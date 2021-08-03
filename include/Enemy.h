#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"


class Enemy: public Entity
{
public:

                    Enemy(const float posX, const float posY, sf::Texture& textureSheet);
    virtual void    update(const float deltaTime, const sf::Vector2f& mousePosView) = 0;

private:

    virtual void    initAnimation() = 0;
    virtual void    updateAnimation(const float deltaTime) = 0;
};


#endif // ENEMY_H
