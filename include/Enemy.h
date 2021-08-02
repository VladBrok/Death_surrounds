#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawner.h"


class Enemy: public Entity
{
public:

                    Enemy(EnemySpawner&, const float posX, const float posY, sf::Texture& textureSheet);
    virtual void    update(const float deltaTime, const sf::Vector2f& mousePosView);
    virtual void    render(sf::RenderTarget& target, 
                           sf::Shader* pShader   = nullptr,
                           const bool showHitbox = false
                           );

private:

    EnemySpawner&   enemySpawner;

    void            updateAnimation(const float deltaTime);
};


#endif // ENEMY_H
