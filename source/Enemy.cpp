#include "precompiled.h"
#include "Enemy.h"


Enemy::Enemy(const float posX, const float posY, const sf::Texture& textureSheet)
    : Entity(textureSheet), expForKilling(0)
{
    setPosition(posX, posY);
}


void Enemy::loseHp(const unsigned hp)
{
    if (pAttributeComponent)
    {
        pAttributeComponent->loseHp(hp);
    }
    else
    {
        std::cout << "ERROR in Enemy::loseHp: this enemy doesn't have an AttributeComponent\n";
    }
}


bool Enemy::isDead() const
{
    if (pAttributeComponent)
    {
        return pAttributeComponent->hp <= 0;
    }
    else
    {
        std::cout << "ERROR in Enemy::isDead: this enemy doesn't have an AttributeComponent\n";
        return false;
    }
}


unsigned Enemy::getExpForKilling() const
{
    return expForKilling;
}
