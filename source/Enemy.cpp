#include "precompiled.h"
#include "Enemy.h"


Enemy::Enemy(const float posX, const float posY, const sf::Texture& textureSheet)
    : Entity(textureSheet), expForKillingMax(0)
{
    setPosition(posX, posY);

    initDamageTimerMax();
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


bool Enemy::canBeDamaged() const
{
    return damageTimer.getElapsedTime().asMilliseconds() >= damageTimerMax;
}


void Enemy::restartDamageTimer()
{
    damageTimer.restart();
}


unsigned Enemy::getExpForKilling() const
{
    if (pAttributeComponent)
    {
        return rand() % (expForKillingMax - pAttributeComponent->level * 2 + 1)  + pAttributeComponent->level * 2;
    }
    else
    {
        return rand() % expForKillingMax + 1;
    }
}


int Enemy::getDamage() const
{
    if (pAttributeComponent)
    {
        return pAttributeComponent->getDamage();
    }
    else
    {
        std::cout << "ERROR in Enemy::isDead: this enemy doesn't have an AttributeComponent\n";
        return 0;
    }
}



void Enemy::initDamageTimerMax()
{
    damageTimerMax = 200;
}
