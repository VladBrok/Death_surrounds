#include "Player.h"
#include <iostream>


Player::Player(const float posX, const float posY, sf::Texture& textureSheet)
    : Entity(textureSheet)
{
    createMovementComponent(230.f, 1300.f, 950.f);

    createAnimationComponent(textureSheet);

    createHitboxComponent(85.f, 70.f, 80.f, 111.f);

    pAnimationComponent->addAnimation(
        "PLAYER_IDLE", textureSheet, sprite, 0, 0, 13, 0, 192, 192, 8.5f
    );
    pAnimationComponent->addAnimation(
        "PLAYER_MOVING", textureSheet, sprite, 0, 1, 11, 1, 192, 192, 8.5f 
    );

    setPosition(posX, posY);
}


Player::~Player()
{
}


void Player::update(const float deltaTime)
{
    Entity::update(deltaTime);

    //try
    //{
    //    pAnimationComponent->play("PLAYER_" + pMovementComponent->getMovementState(), deltaTime);
    //}
    //catch(std::out_of_range&)
    //{
    //    std::cout << "There is no animation for this type of player movement.\n";
    //}

    if (pMovementComponent->getMovementState() == "IDLE")
    {
        pAnimationComponent->play("PLAYER_IDLE", deltaTime);
    }
    else if (pMovementComponent->getMovementState() == "MOVING_LEFT")
    {
        sprite.setOrigin(0.f, 0.f);
        sprite.setScale(1.f, 1.f);
        pAnimationComponent->play("PLAYER_MOVING", deltaTime);
    }
    else if (pMovementComponent->getMovementState() == "MOVING_RIGHT")
    {
        sprite.setOrigin(258.f, 0.f);
        sprite.setScale(-1.f, 1.f); // Flipping the texture by changing scale of sprite
        pAnimationComponent->play("PLAYER_MOVING", deltaTime);
    }
    else
    {
        pAnimationComponent->play("PLAYER_MOVING", deltaTime);
    }

    pHitboxComponent->update();
}
