#include "precompiled.h"
#include "Entity.h"
#include "constants.h"


Entity::Entity(const sf::Texture& texture)
    : texture(texture),
      sprite(texture), 
      pMovementComponent(nullptr), 
      pAnimationComponent(nullptr),
      pHitboxComponent(nullptr),
      pAttributeComponent(nullptr)
{ 
}


Entity::~Entity()
{
    delete pMovementComponent;
    delete pAnimationComponent;
    delete pHitboxComponent;
    delete pAttributeComponent;
}


void Entity::render(sf::RenderTarget& target, 
                    sf::Shader* pShader,
                    const sf::Vector2f& shaderLightPosition,
                    const bool showHitbox
                    )
{
    if (pShader)
    {
        pShader->setParameter("hasTexture", true);
        pShader->setParameter("light", shaderLightPosition);

        target.draw(sprite, pShader);
    }
    else
    {
        target.draw(sprite);
    }

    if (pHitboxComponent && showHitbox)
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


void Entity::setPosition(const float posX, const float posY)
{
    if (pHitboxComponent)
    {
        pHitboxComponent->setPosition(posX, posY);
    }
    else
    {
        sprite.setPosition(posX, posY);
    }
}


const sf::Vector2f& Entity::getPosition() const
{
    if (pHitboxComponent)
    {
        return pHitboxComponent->getPosition();
    }
    return sprite.getPosition();
}


const sf::Vector2i Entity::getGridPosition() const
{
    if (pHitboxComponent)
    {
        return sf::Vector2i(
            static_cast<sf::Vector2i>(pHitboxComponent->getPosition()) / static_cast<int>(GRID_SIZE)
        );
    }
    return static_cast<sf::Vector2i>(sprite.getPosition()) / static_cast<int>(GRID_SIZE);
}


const sf::Vector2f Entity::getCenter() const
{
    if (pHitboxComponent)
    {
        return pHitboxComponent->getPosition() + 
                   sf::Vector2f(
                        pHitboxComponent->getGlobalBounds().width / 2.f,
                        pHitboxComponent->getGlobalBounds().height / 2.f
                   );
    }
    return sprite.getPosition() + 
               sf::Vector2f(
                    sprite.getGlobalBounds().width / 2.f,
                    sprite.getGlobalBounds().height / 2.f
               );
}


const sf::Vector2i Entity::getGridPositionCenter() const
{
    return static_cast<sf::Vector2i>(getCenter()) / static_cast<int>(GRID_SIZE);
}


const sf::FloatRect Entity::getGlobalBounds() const
{
    if (pHitboxComponent)
    {
        return pHitboxComponent->getGlobalBounds();
    }
    return sprite.getGlobalBounds();
}


const sf::FloatRect Entity::getNextPositionBounds(const float deltaTime) const
{
    if (pHitboxComponent && pMovementComponent)
    {
        return pHitboxComponent->getNextPositionBounds(pMovementComponent->getVelocity() * deltaTime);
    }
    return sprite.getGlobalBounds();
}


void Entity::stopVelocity()
{
    if (pMovementComponent)
    {
        pMovementComponent->stopVelocity();
    }
}


void Entity::stopVelocityX()
{
    if (pMovementComponent)
    {
        pMovementComponent->stopVelocityX();
    }
}


void Entity::stopVelocityY()
{
    if (pMovementComponent)
    {
        pMovementComponent->stopVelocityY();
    }
}


void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    pMovementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}


void Entity::createAnimationComponent(const sf::Texture& textureSheet)
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


void Entity::createAttributeComponent(const unsigned level, 
                                      const int hpMax, 
                                      const int damageMin, 
                                      const int damageMax
                                      )
{
    pAttributeComponent = new AttributeComponent(level, hpMax, damageMin, damageMax);
}
