#ifndef RAT_H
#define RAT_H

#include "Enemy.h"


class Rat: public Enemy
{
public:

                    Rat(const float posX, const float posY, sf::Texture& textureSheet);
    virtual void    update(const float deltaTime, const sf::Vector2f& mousePosView);

private:

    virtual void    initAnimation();
    virtual void    updateAnimation(const float deltaTime);
};


#endif // RAT_H
