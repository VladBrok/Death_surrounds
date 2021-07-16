#include "Entity.h"


Entity::Entity(const sf::Texture& texture)
    : sprite(texture), pMovementComponent(nullptr)
{ 

    // FIXME
    sprite.setScale(0.2f, 0.2f);

}


Entity::~Entity()
{
    delete pMovementComponent;
}


void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    pMovementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}


void Entity::setPosition(const float posX, const float posY)
{
    sprite.setPosition(posX, posY);
}


void Entity::update(const float deltaTime)
{
    if (pMovementComponent)
    {
        pMovementComponent->updateMovement(deltaTime);
    }
}


void Entity::render(sf::RenderTarget* target)
{
    target->draw(sprite);
}


void Entity::move(const float dirX, const float dirY, const float deltaTime)
{
    if (pMovementComponent)
    {
        pMovementComponent->accelerateSprite(sf::Vector2f(dirX, dirY), deltaTime);
    }
}