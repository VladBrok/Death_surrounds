#include "precompiled.h"
#include "MovementComponent.h"


MovementComponent::MovementComponent(sf::Sprite& sprite,
                                     const float maxVelocity,
                                     const float acceleration,
                                     const float deceleration
                                     )
    : sprite(sprite), 
      maxVelocity(maxVelocity), 
      acceleration(acceleration), 
      deceleration(deceleration),
      velocity(0.f, 0.f)
{
}


void MovementComponent::accelerateSprite(const sf::Vector2f& movementDirection,
                                         const float deltaTime
                                         )
{
    velocity.x += acceleration * movementDirection.x * deltaTime;
    velocity.y += acceleration * movementDirection.y * deltaTime;
}


void MovementComponent::updateMovement(const float deltaTime)
{
    if (getMovementState() == "IDLE")
    {
        return;
    }

    decelerateAndCheckVelocityBounds(deltaTime);

    sprite.move(velocity * deltaTime);
}


const sf::Vector2f& MovementComponent::getVelocity() const
{
    return velocity;
}


float MovementComponent::getMaxVelocity() const
{
    return maxVelocity;
}


const std::string MovementComponent::getMovementState() const
{
    if (velocity.x == 0.f && velocity.y == 0.f)
    {
        return std::string("IDLE");
    }
    if (velocity.x < 0.f)
    {
        return std::string("MOVING_LEFT");
    }
    if (velocity.x > 0.f)
    {
        return std::string("MOVING_RIGHT");
    }
    if (velocity.y < 0.f)
    {
        return std::string("MOVING_UP");
    }
    if (velocity.y > 0.f)
    {
        return std::string("MOVING_DOWN");
    }
    return std::string("ERROR");
}


void MovementComponent::stopVelocity()
{
    velocity.x = velocity.y = 0.f;
}


void MovementComponent::stopVelocityX()
{
    velocity.x = 0.f;
}


void MovementComponent::stopVelocityY()
{
    velocity.y = 0.f;
}


void MovementComponent::decelerateAndCheckVelocityBounds(const float deltaTime)
{
    if (velocity.x > 0.f)
    {
        deceleratePositiveVelocity(velocity.x, deltaTime);
    }
    else if (velocity.x < 0.f)
    {
        decelerateNegativeVelocity(velocity.x, deltaTime);
    }

    if (velocity.y > 0.f)
    {
        deceleratePositiveVelocity(velocity.y, deltaTime);
    }
    else if (velocity.y < 0.f)
    {
        decelerateNegativeVelocity(velocity.y, deltaTime);
    }
}


void MovementComponent::deceleratePositiveVelocity(float& velocity, 
                                                   const float deltaTime
                                                   )
{
        velocity -= deceleration * deltaTime;
        velocity = std::min(velocity, maxVelocity);
        velocity = std::max(velocity, 0.f);
}


void MovementComponent::decelerateNegativeVelocity(float& velocity, 
                                                   const float deltaTime
                                                   )
{
        velocity += deceleration * deltaTime;
        velocity = std::max(velocity, -maxVelocity);
        velocity = std::min(velocity, 0.f);
}