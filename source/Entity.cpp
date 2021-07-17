#include "Entity.h"


Entity::Entity(const sf::Texture& texture)
    : sprite(texture), 
      pMovementComponent(nullptr), 
      pAnimationComponent(nullptr),
      pHitboxComponent(nullptr)
{ 
}


Entity::~Entity()
{
    delete pMovementComponent;
    delete pAnimationComponent;
    delete pHitboxComponent;
}


void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    pMovementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}


void Entity::createAnimationComponent(sf::Texture& textureSheet)
{
    pAnimationComponent = new AnimationComponent(textureSheet, sprite);
}


void Entity::createHitboxComponent(const float offsetFromSpritePositionX,
                                   const float offsetFromSpritePositionY,
                                   const float hitboxWidth,
                                   const float hitboxHeight
                                   )
{
    pHitboxComponent = new HitboxComponent(
                              sprite, 
                              offsetFromSpritePositionX, 
                              offsetFromSpritePositionY,
                              hitboxWidth,
                              hitboxHeight
                           );
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


void Entity::render(sf::RenderTarget& target)
{
    target.draw(sprite);
    if (pHitboxComponent)
    {
        pHitboxComponent->render(target);
    }
}


void Entity::move(const float dirX, const float dirY, const float deltaTime)
{
    if (pMovementComponent)
    {
        pMovementComponent->accelerateSprite(sf::Vector2f(dirX, dirY), deltaTime);
    }
}