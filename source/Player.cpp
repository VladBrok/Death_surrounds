#include "precompiled.h"
#include "Player.h"


Player::Player(const float posX, const float posY, sf::Texture& textureSheet)
    : Entity(textureSheet), isAttacking(false)
{
    createMovementComponent(200.f, 1600.f, 1000.f);

    createAnimationComponent(textureSheet);

    createHitboxComponent(17.f, 9.f, 30.f, 50.f);

    createAttributeComponent(1);


    pAnimationComponent->addAnimation(
        "PLAYER_IDLE", textureSheet, sprite, 0, 0, 8, 0, 64, 64, 9.5f
    );

    pAnimationComponent->addAnimation(
        "PLAYER_MOVING_DOWN", textureSheet, sprite, 0, 1, 3, 1, 64, 64, 9.5f 
    );

    pAnimationComponent->addAnimation(
        "PLAYER_MOVING_LEFT", textureSheet, sprite, 4, 1, 7, 1, 64, 64, 9.5f 
    );

    pAnimationComponent->addAnimation(
        "PLAYER_MOVING_RIGHT", textureSheet, sprite, 8, 1, 11, 1, 64, 64, 9.5f 
    );

    pAnimationComponent->addAnimation(
        "PLAYER_MOVING_UP", textureSheet, sprite, 12, 1, 15, 1, 64, 64, 9.5f 
    );

    setPosition(posX, posY);
}


Player::~Player()
{
}


void Player::update(const float deltaTime)
{
    pMovementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    pHitboxComponent->update();
}


int Player::getHP() const
{
    return pAttributeComponent->hp;
}


int Player::getHPMax() const
{
    return pAttributeComponent->hpMax;
}


int Player::getExp() const
{
    return pAttributeComponent->exp;
}


int Player::getExpForNextLevel() const
{
    return pAttributeComponent->expForNextLevel;
}


unsigned Player::getLevel() const
{
    return pAttributeComponent->level;
}


void Player::loseHP(const unsigned points)
{
    pAttributeComponent->loseHP(points);
}


void Player::gainHP(const unsigned points)
{
    pAttributeComponent->gainHP(points);
}


void Player::loseExp(const unsigned exp)
{
    pAttributeComponent->loseExp(exp);
}


void Player::gainExp(const unsigned exp)
{
    pAttributeComponent->gainExp(exp);
}


void Player::updateAttack()
{
    //if (isAttacking && pAnimationComponent->isDone("PLAYER_ATTACKING"))
    //{
    //    isAttacking = false;

    //    // Changing the origin of the sprite to normal
    //    if (sprite.getScale().x < 0.f) // Facing right
    //    {
    //        sprite.setOrigin(258.f, 0.f);
    //    }
    //    else // Facing left
    //    {
    //        sprite.setOrigin(0.f, 0.f);
    //    }
    //}
    //if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //{
    //    isAttacking = true;

    //    // Changing the origin of the sprite in order to adjust hitbox position
    //    if (sprite.getScale().x < 0.f) // Facing right
    //    {
    //        sprite.setOrigin(258.f + 96.f, 0.f);
    //    }
    //    else // Facing left
    //    {
    //        sprite.setOrigin(96.f, 0.f);
    //    }
    //}
}


void Player::updateAnimation(const float deltaTime)
{
    try
    {
        const std::string movementState(pMovementComponent->getMovementState());

        // Playing the idle animation without any modifiers for animation speed
        if (movementState == "IDLE")
        {
            pAnimationComponent->play("PLAYER_IDLE", deltaTime);
        }

        // Playing the movement animations using the player's velocity as modifier for animation speed
        else
        {
            float modifier = (movementState == "MOVING_RIGHT" || movementState == "MOVING_LEFT") ? pMovementComponent->getVelocity().x: pMovementComponent->getVelocity().y;
            float modifierMax = pMovementComponent->getMaxVelocity();

            pAnimationComponent->play(
                "PLAYER_" + movementState, 
                deltaTime, 
                modifier,
                modifierMax
            ); 
        }
 
    }
    catch(std::out_of_range&)
    {
        std::cout << "ERROR in Player::updateAnimation:\nthere is no animation for this type of player movement.\n";
    }
}
