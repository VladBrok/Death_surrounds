#include "MovementComponent.h"
#include <iostream>


MovementComponent::MovementComponent(sf::Sprite& sprite, const float maxVelocity,
                                     const float acceleration, const float deceleration
                                    )
    : sprite(sprite), 
      maxVelocity(maxVelocity), 
      acceleration(acceleration), 
      deceleration(deceleration),
      velocity(0.f, 0.f)
{
}


void MovementComponent::accelerateSprite(const sf::Vector2f& movementDirection, const float deltaTime)
{
    velocity.x += acceleration * movementDirection.x * deltaTime;
    velocity.y += acceleration * movementDirection.y * deltaTime;
}


const sf::Vector2f& MovementComponent::getVelocity() const
{
    return velocity;
}


void MovementComponent::updateMovement(const float deltaTime)
{
    if (isIdle())
    {
        return;
    }

    decelerateSpriteAndCheckVelocityBounds(deltaTime);

    sprite.move(velocity * deltaTime);
    
    ////////////////////
    // DEBUG
    std::cout << velocity.x << ' ' << velocity.y << '\n';
    /////////////////
}


const bool MovementComponent::isIdle() const
{
    return (velocity.x == 0.f) && (velocity.y == 0.f);
}


void MovementComponent::decelerateSpriteAndCheckVelocityBounds(const float deltaTime)
{
    // Checking x
    if (velocity.x > 0.f)
    {
        velocity.x -= deceleration * deltaTime;

        if (velocity.x > maxVelocity)
        {
            velocity.x = maxVelocity;
        }

        if (velocity.x < 0.f)
        {
            velocity.x = 0.f;
        }
    }
    else if (velocity.x < 0.f)
    {
        velocity.x += deceleration * deltaTime;

        if (velocity.x < -maxVelocity)
        {
            velocity.x = -maxVelocity;
        }

        if (velocity.x > 0.f)
        {
            velocity.x = 0.f;
        }
    }

    // Checking y
    if (velocity.y > 0.f)
    {
        velocity.y -= deceleration * deltaTime;

        if (velocity.y > maxVelocity)
        {
            velocity.y = maxVelocity;
        }

        if (velocity.y < 0.f)
        {
            velocity.y = 0.f;
        }
    }
    else if (velocity.y < 0.f)
    {
        velocity.y += deceleration * deltaTime;

        if (velocity.y < -maxVelocity)
        {
            velocity.y = -maxVelocity;
        }

        if (velocity.y > 0.f)
        {
            velocity.y = 0.f;
        }
    }
}