#include "precompiled.h"
#include "AiSpawnMinion.h"
#include "Entity.h"
#include "Utils.h"


AiSpawnMinion::AiSpawnMinion(Entity& self, 
                             const EnemyType minionType, 
                             const float spawnFrequencyInSeconds,
                             const int minionsToSpawnAtOnceFrom1To2
                             )
    : self(self),
      minionType(minionType), 
      spawnTimerMax(spawnFrequencyInSeconds),
      minionsToSpawnAtOnce(minionsToSpawnAtOnceFrom1To2)
{
    assert(minionsToSpawnAtOnceFrom1To2 >= 1 && minionsToSpawnAtOnceFrom1To2 <= 2);
}


void AiSpawnMinion::update(EnemySystem& enemySystem)
{
    if (spawnTimer.getElapsedTime().asSeconds() >= spawnTimerMax)
    {
        spawnTimer.restart();
 
        float spawnOffset = self.getGlobalBounds().height * 1.5f;
        int toSpawnCount = minionsToSpawnAtOnce;
        while (toSpawnCount)
        {
            enemySystem.createEnemy(self.getCenter().x, self.getCenter().y + spawnOffset, minionType);
            --toSpawnCount;
            spawnOffset = -spawnOffset;
        }
    }
}
