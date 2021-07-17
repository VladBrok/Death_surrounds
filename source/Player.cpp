#include "Player.h"


Player::Player(const float posX, const float posY, sf::Texture& textureSheet)
    : Entity(textureSheet)
{
    createMovementComponent(160.f, 1400.f, 1000.f);

    createAnimationComponent(textureSheet, sprite);
    pAnimationComponent->addAnimation(
        "PLAYER_IDLE", textureSheet, sprite, 0, 0, 13, 0, 192, 192, 10.f
    );
    pAnimationComponent->addAnimation(
        "PLAYER_MOVING_LEFT", textureSheet, sprite, 0, 1, 11, 1, 192, 192, 10.f 
    );

    setPosition(posX, posY);
}


Player::~Player()
{
}


void Player::update(const float deltaTime)
{
    Entity::update(deltaTime);

    if (pMovementComponent->isIdle())
    {
        pAnimationComponent->play("PLAYER_IDLE", deltaTime);
    }
    else
    {
        pAnimationComponent->play("PLAYER_MOVING_LEFT", deltaTime);
    }
}
