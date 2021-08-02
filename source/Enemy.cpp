#include "precompiled.h"
#include "Enemy.h"


Enemy::Enemy(const float posX, const float posY, sf::Texture& textureSheet)
    : Entity(textureSheet)
{

    createMovementComponent(200.f, 1600.f, 1000.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(17.f, 9.f, 30.f, 50.f);

    pAnimationComponent->addAnimation("IDLE", textureSheet, sprite, 0, 0, 3, 0, 60, 64, 15.f);
    pAnimationComponent->addAnimation("MOVING_DOWN", textureSheet, sprite, 0, 1, 3, 1, 60, 64, 11.f);
    pAnimationComponent->addAnimation("MOVING_LEFT", textureSheet, sprite, 0, 2, 3, 2, 60, 64, 11.f);
    pAnimationComponent->addAnimation("MOVING_RIGHT", textureSheet, sprite, 0, 3, 3, 3, 60, 64, 11.f);
    pAnimationComponent->addAnimation("MOVING_UP", textureSheet, sprite, 0, 4, 3, 4, 60, 64, 11.f );

    setPosition(posX, posY);
}


void Enemy::update(const float deltaTime, const sf::Vector2f& mousePosView)
{
    pMovementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    pHitboxComponent->update();
}


void Enemy::render(sf::RenderTarget& target, 
                    sf::Shader* pShader,
                    const sf::Vector2f& shaderLightPosition,
                    const bool showHitbox
                    )
{
    Entity::render(target, pShader, shaderLightPosition, showHitbox);
}


void Enemy::updateAnimation(const float deltaTime)
{
    try
    {
        const std::string& movementState = pMovementComponent->getMovementState();

        // Playing animations using the enemy's velocity as modifier for animation speed
        float modifier = (movementState == "MOVING_RIGHT" || movementState == "MOVING_LEFT") ? pMovementComponent->getVelocity().x: pMovementComponent->getVelocity().y;
        float modifierMax = pMovementComponent->getMaxVelocity();

        pAnimationComponent->play(
            movementState, 
            deltaTime, 
            modifier,
            modifierMax
        ); 
    }
    catch(std::out_of_range&)
    {
        std::cout << "ERROR in Enemy::updateAnimation:\nthere is no animation for this type of enemy movement.\n";
    }
}
