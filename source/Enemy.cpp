#include "precompiled.h"
#include "Enemy.h"


Enemy::Enemy(const float posX, const float posY, sf::Texture& textureSheet)
    : Entity(textureSheet)
{
    setPosition(posX, posY);
}
