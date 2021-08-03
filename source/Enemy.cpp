#include "precompiled.h"
#include "Enemy.h"


Enemy::Enemy(const float posX, const float posY, const sf::Texture& textureSheet)
    : Entity(textureSheet)
{
    setPosition(posX, posY);
}

