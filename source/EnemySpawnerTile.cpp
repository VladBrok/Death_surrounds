#include "precompiled.h"
#include "EnemySpawnerTile.h"
#include "EnemySystem.h"


EnemySpawnerTile::EnemySpawnerTile(const float posX, 
                                   const float posY, 
                                   const sf::Texture& textureSheet,
                                   const sf::IntRect& textureRect,
                                   const bool canCollide,
                                   const int enemyType,
                                   const int enemyTimeToSpawn
                                   )
    : Tile(ENEMY_SPAWNER, posX, posY, textureSheet, textureRect, canCollide),
      enemyType(enemyType),
      enemyTimeToSpawn(enemyTimeToSpawn),
      firstSpawn(true)
{
}


void EnemySpawnerTile::update(EnemySystem& enemySystem)
{
    if (spawnTimer.getElapsedTime().asSeconds() >= (float)enemyTimeToSpawn ||
        firstSpawn)
    {
        spawnTimer.restart();

        enemySystem.createEnemy(getPosition().x, getPosition().y, enemyType);

        firstSpawn = false;
    }
}


const std::string EnemySpawnerTile::getAsString() const
{
    std::stringstream stream;

    stream << textureRect.left << ' ' << textureRect.top << ' ' << canCollide << ' ' << enemyType << ' ' << ' ' << enemyTimeToSpawn;

    return stream.str();
}