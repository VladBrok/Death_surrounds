#include "precompiled.h"
#include "EnemySpawnerTile.h"
#include "constants.h"
#include "EnemySystem.h"


EnemySpawnerTile::EnemySpawnerTile(const float posX, 
                                   const float posY, 
                                   const sf::Texture& textureSheet,
                                   const sf::IntRect& textureRect,
                                   const bool canCollide,
                                   const int enemyType,
                                   const int enemyAmount,
                                   const int enemyTimeToSpawn,
                                   const float enemyMaxDistance
                                   )
    : Tile(ENEMY_SPAWNER, posX, posY, textureSheet, textureRect, canCollide),
      enemyType(enemyType),
      enemyAmount(enemyAmount),
      enemyTimeToSpawn(enemyTimeToSpawn),
      enemyMaxDistance(enemyMaxDistance),
      spawnTimer(0),
      currentEnemyAmount(0)
{
}


void EnemySpawnerTile::update(EnemySystem& enemySystem, const float deltaTime)
{
    spawnTimer += static_cast<int>(deltaTime * (1000.f / 16.f));
    currentEnemyAmount = enemySystem.getNumberOfActiveEnemies();

    if (spawnTimer >= enemyTimeToSpawn && currentEnemyAmount < enemyAmount)
    {
        spawnTimer = 0;

        enemySystem.createEnemy(getPosition().x, getPosition().y, enemyType);
    }
}


const std::string EnemySpawnerTile::getAsString() const
{
    std::stringstream stream;

    stream << textureRect.left << ' ' << textureRect.top << ' ' << canCollide << ' ' << enemyType << ' ' << enemyAmount << ' ' << enemyTimeToSpawn << ' ' << enemyMaxDistance;

    return stream.str();
}