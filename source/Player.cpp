#include "Player.h"


Player::Player(const float posX, const float posY, sf::Texture& textureSheet)
    : Entity(textureSheet)
{
    createMovementComponent(160.f, 1400.f, 1000.f);

    createAnimationComponent(textureSheet, sprite);
    pAnimationComponent->addAnimation("PLAYER_IDLE", textureSheet, sprite, 0, 13, 192, 192, 10.f);

    setPosition(posX, posY);
}


Player::~Player()
{
}


void Player::update(const float deltaTime)
{
    Entity::update(deltaTime);

    pAnimationComponent->play("PLAYER_IDLE", deltaTime);
}
