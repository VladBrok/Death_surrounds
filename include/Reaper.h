#ifndef REAPER_H
#define REAPER_H

#include "Enemy.h"
#include "AiFollow.h"
#include "AiSpawnMinion.h"


class Reaper: public Enemy
{
public:
                          Reaper(const float posX, 
                                 const float posY, 
                                 const sf::Texture& textureSheet, 
                                 const sf::Texture& lootTextureSheet, 
                                 Entity& player,
                                 EnemySystem& enemySystem
                                 );
                      ~Reaper();
    virtual void      update(const float deltaTime);

private:

    AiSpawnMinion*    pAiSpawnMinion;
    AiFollow*         pAiFollow;
    EnemySystem&      enemySystem;

    virtual void      initAnimation();
    virtual void      initDroppingItem();
};


#endif // REAPER_H
