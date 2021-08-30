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
    virtual void                 update(const float deltaTime);
                                 
private:                         
                                 
    std::unique_ptr<AiFollow>    aiFollow;
                                 
    virtual void                 initAnimation();
    virtual void                 initDroppingItem();
};


#endif // RAT_H
