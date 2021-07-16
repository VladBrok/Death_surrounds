#include "Entity.h"


Entity::Entity(const sf::Texture& texture)
    : sprite(texture), pMovementComponent(nullptr), pAnimationComponent(nullptr)
{ 
}


Entity::~Entity()
{
    delete pMovementComponent;
    delete pAnimationComponent;
}


void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    pMovementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}


void Entity::createAnimationComponent(sf::Texture& textureSheet, sf::Sprite& sprite)
{
    pAnimationComponent = new AnimationComponent(textureSheet, sprite);
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