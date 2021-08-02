#include "precompiled.h"
#include "EnemySpawner.h"
#include "constants.h"


EnemySpawner::EnemySpawner(const float posX, 
                           const float posY, 
                           const sf::Texture& textureSheet,
                           const sf::IntRect& textureRect,
                           const int enemyType,
                           const int enemyAmount,
                           const int enemyTimeToSpawn,
                           const float enemyMaxDistance
                           )
    : Tile(posX, posY, textureSheet, textureRect, false, ENEMY_SPAWNER),
      enemyType(enemyType),
      enemyAmount(enemyAmount),
      enemyTimeToSpawn(enemyTimeToSpawn),
      enemyMaxDistance(enemyMaxDistance)
{
}


void EnemySpawner::update()
{
}


void EnemySpawner::render(sf::RenderTarget& target,
                          sf::Shader* pShader,
                          const sf::Vector2f& shaderLightPosition
                          )
{
    Tile::render(target, pShader, shaderLightPosition);
}