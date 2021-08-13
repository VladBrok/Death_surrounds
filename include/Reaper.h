#ifndef REAPER_H
#define REAPER_H

#include "Enemy.h"
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
    EnemySystem&      enemySystem;

    virtual void      updateAnimation(const float deltaTime);
    virtual void      initAttributeComponent();
    virtual void      initAnimation();
    virtual void      initDroppingItem();
};


#endif // REAPER_H
