#include "precompiled.h"
#include "Enemy.h"
#include "Utils.h"


Enemy::Enemy(const float posX, 
             const float posY, 
             const sf::Texture& textureSheet,
             const sf::Texture& lootTextureSheet
             )
    : Character(textureSheet), lootTextureSheet(lootTextureSheet), expForKillingMax(0)
{
    setPosition(posX, posY);

    initTimers();
}


bool Enemy::canBeDespawned(const sf::View& view) const
{
    return utils::getDistance(getCenter(), view.getCenter()) > (view.getSize().x + view.getSize().y) / 2.0f;
}


int Enemy::getExpForKilling() const
{
    if (attributeComponent)
    {
        return rand() % (expForKillingMax - attributeComponent->getLevel() * 2 + 1)  + attributeComponent->getLevel() * 2;
    }
    else
    {
        return rand() % expForKillingMax + 1;
    }
}


Item* Enemy::getDroppingItem() const
{
    return droppingItem.get();
}


void Enemy::updateAnimation(const float deltaTime)
{
    if (movementComponent->getMovementState() == "IDLE")
    {
        return;
    }
    Character::updateAnimation(deltaTime);
}


void Enemy::initTimers()
{
    damageTimerMax = 200;
    attackTimerMax = 200;
}
