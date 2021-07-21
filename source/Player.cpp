#include "precompiled.h"
#include "Player.h"


Player::Player(const float posX, const float posY, sf::Texture& textureSheet)
    : Entity(textureSheet), isAttacking(false)
{
    createMovementComponent(350.f, 15.f * 62.5f, 10.f * 62.5f);

    createAnimationComponent(textureSheet);

    createHitboxComponent(85.f, 70.f, 80.f, 111.f);

    pAnimationComponent->addAnimation(
        "PLAYER_IDLE", textureSheet, sprite, 0, 0, 13, 0, 192, 192, 8.5f
    );
    pAnimationComponent->addAnimation(
        "PLAYER_MOVING", textureSheet, sprite, 0, 1, 11, 1, 192, 192, 8.5f 
    );
    pAnimationComponent->addAnimation(
        "PLAYER_ATTACKING", textureSheet, sprite, 0, 2, 13, 2, 384, 192, 5.f
    );

    setPosition(posX, posY);
}


Player::~Player()
{
}


void Player::update(const float deltaTime)
{
    Entity::update(deltaTime);

    updateAttack();

    updateAnimation(deltaTime);

    pHitboxComponent->update();
}


void Player::updateAttack()
{
    if (isAttacking && pAnimationComponent->isDone("PLAYER_ATTACKING"))
    {
        isAttacking = false;

        // Changing the origin of the sprite to normal
        if (sprite.getScale().x < 0.f) // Facing right
        {
            sprite.setOrigin(258.f, 0.f);
        }
        else // Facing left
        {
            sprite.setOrigin(0.f, 0.f);
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        isAttacking = true;

        // Changing the origin of the sprite in order to adjust hitbox position
        if (sprite.getScale().x < 0.f) // Facing right
        {
            sprite.setOrigin(258.f + 96.f, 0.f);
        }
        else // Facing left
        {
            sprite.setOrigin(96.f, 0.f);
        }
    }
}


void Player::updateAnimation(const float deltaTime)
{
    //try
    //{
    //    pAnimationComponent->play("PLAYER_" + pMovementComponent->getMovementState(), deltaTime);
    //}
    //catch(std::out_of_range&)
    //{
    //    std::cout << "There is no animation for this type of player movement.\n";
    //}/

    


    /* Playing animations */

    // Attack
    if (isAttacking)
    {
        pAnimationComponent->play("PLAYER_ATTACKING", deltaTime, true);
    }

    // Idle
    else if (pMovementComponent->getMovementState() == "IDLE")
    {
        pAnimationComponent->play("PLAYER_IDLE", deltaTime);
    }

    // Moving left
    else if (pMovementComponent->getMovementState() == "MOVING_LEFT")
    {
        if (sprite.getScale().x < 0.f) // Facing right
        {
            sprite.setOrigin(0.f, 0.f);
            sprite.setScale(1.f, 1.f);
        }

        pAnimationComponent->play("PLAYER_MOVING", deltaTime, pMovementComponent->getVelocity().x, pMovementComponent->getMaxVelocity());
    }

    // Moving right
    else if (pMovementComponent->getMovementState() == "MOVING_RIGHT")
    {
        if (sprite.getScale().x > 0.f) // Facing left
        {
            sprite.setOrigin(258.f, 0.f);
            sprite.setScale(-1.f, 1.f); // Flipping the texture by changing scale of sprite
        }

        pAnimationComponent->play("PLAYER_MOVING", deltaTime, pMovementComponent->getVelocity().x, pMovementComponent->getMaxVelocity());
    }

    // Moving up or down
    else
    {
        pAnimationComponent->play("PLAYER_MOVING", deltaTime, pMovementComponent->getVelocity().y, pMovementComponent->getMaxVelocity());
    }
}
