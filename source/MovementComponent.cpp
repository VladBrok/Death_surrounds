#include "MovementComponent.h"


MovementComponent::MovementComponent(const float maxVelocity)
    : maxVelocity(maxVelocity)
{
}


void MovementComponent::setVelocity(const sf::Vector2f& movementDirection)
{
    this->velocity = movementDirection * maxVelocity;
}


const sf::Vector2f& MovementComponent::getVelocity() const
{
    return velocity;
}