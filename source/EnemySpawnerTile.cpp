#include "precompiled.h"
#include "EnemySpawnerTile.h"
#include "constants.h"


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
      enemyMaxDistance(enemyMaxDistance)
{
}


void EnemySpawnerTile::update()
{
}


const std::string EnemySpawnerTile::getAsString() const
{
    std::stringstream stream;

    stream << textureRect.left << ' ' << textureRect.top << ' ' << canCollide << ' ' << enemyType << ' ' << enemyAmount << ' ' << enemyTimeToSpawn << ' ' << enemyMaxDistance;

    return stream.str();
}