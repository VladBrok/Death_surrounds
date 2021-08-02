#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Tile.h"


class EnemySpawner: public Tile
{
public:

                       EnemySpawner(const float posX, 
                                    const float posY, 
                                    const sf::Texture& textureSheet,
                                    const sf::IntRect& textureRect,
                                    const int enemyType,
                                    const int enemyAmount,
                                    const int enemyTimeToSpawn,
                                    const float enemyMaxDistance
                                    );
    virtual void       update();          
    virtual void       render(sf::RenderTarget& target,
                              sf::Shader* pShader = nullptr,
                              const sf::Vector2f& shaderLightPosition = sf::Vector2f()
                              );

private:

    int                enemyType;
    int                enemyAmount;
    int                enemyTimeToSpawn;
    float              enemyMaxDistance;
};


#endif // ENEMYSPAWNER_H
