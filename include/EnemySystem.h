#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "typedefs.h"
class Enemy;
class Entity;


enum EnemyType
{
    RAT,
    SPIDER,
    SKELETON,
    REAPER,
    NUMBER_OF_ENEMY_TYPES
};


class EnemySystem: public sf::NonCopyable
{
public:

                                       EnemySystem(std::list<std::unique_ptr<Enemy>>& activeEnemies, 
                                                   StringToTextureMap& textures,
                                                   Entity& player
                                                   );
     void                              createEnemy(const float posX,
                                                   const float posY,
                                                   const int type
                                                   );
     static const std::string          getEnemyTypeAsString(const int type);
     int                               getNumberOfActiveEnemies() const;
                                
private:                        
                                
    std::list<std::unique_ptr<Enemy>>& activeEnemies;
    StringToTextureMap&                textures;
    Entity&                            player;
};


#endif // ENEMYSYSTEM_H
