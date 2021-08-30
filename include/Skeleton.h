#ifndef SKELETON_H
#define SKELETON_H

#include "Enemy.h"
#include "AiFollow.h"


class Skeleton: public Enemy
{
public:

                                 Skeleton(const float posX, 
                                          const float posY, 
                                          const sf::Texture& textureSheet, 
                                          const sf::Texture& lootTextureSheet, 
                                          Entity& player
                                          );
    virtual void                 update(const float deltaTime);

private:

    std::unique_ptr<AiFollow>    aiFollow;

    virtual void                 initAnimation();
    virtual void                 initDroppingItem();
};


#endif // SKELETON_H
