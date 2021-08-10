#ifndef RAT_H
#define RAT_H

#include "Enemy.h"
#include "AiFollow.h"


class Rat: public Enemy
{
public:

                    Rat(const float posX, 
                        const float posY, 
                        const sf::Texture& textureSheet, 
                        const sf::Texture& lootTextureSheet, 
                        Entity& player
                        );
                    ~Rat();
    virtual void    update(const float deltaTime, const sf::Vector2f& mousePosView);

private:

    AiFollow*       pAiFollow;

    virtual void    updateAnimation(const float deltaTime);
    virtual void    initAnimation();
    virtual void    initDroppingItem();
};


#endif // RAT_H
