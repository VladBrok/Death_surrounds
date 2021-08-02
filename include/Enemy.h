#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"


class Enemy: public Entity
{
public:

                    Enemy(const float posX, const float posY, sf::Texture& textureSheet);
    virtual void    update(const float deltaTime, const sf::Vector2f& mousePosView);
    virtual void    render(sf::RenderTarget& target, 
                           sf::Shader* pShader   = nullptr,
                           const sf::Vector2f& shaderLightPosition = sf::Vector2f(),
                           const bool showHitbox = false
                           );

private:

    void            updateAnimation(const float deltaTime);
};


#endif // ENEMY_H
