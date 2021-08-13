#ifndef AISPAWNMINION_H
#define AISPAWNMINION_H

#include "EnemySystem.h"


class AiSpawnMinion: public sf::NonCopyable
{
public:

                 AiSpawnMinion(Entity& self, 
                               const EnemyType minionType, 
                               const float spawnFrequencyInSeconds,
                               const int minionsToSpawnAtOnceFrom1To2
                               );
                 
    void         update(EnemySystem& enemySystem);
                 
private:         
                 
    Entity&      self;
    EnemyType    minionType;
    sf::Clock    spawnTimer;
    float        spawnTimerMax;
    int          minionsToSpawnAtOnce;
};


#endif // AISPAWNMINION_H
