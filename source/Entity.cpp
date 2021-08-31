#include "precompiled.h"
#include "Entity.h"
#include "constants.h"


Entity::Entity(const sf::Texture& texture)
    : texture(texture),
      sprite(texture), 
      movementComponent(nullptr), 
      animationComponent(nullptr),
      hitboxComponent(nullptr),
      attributeComponent(nullptr)
{ 
}


Entity::~Entity()
{
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

    if (hitboxComponent && showHitbox)
    {
        hitboxComponent->render(target);
    }
}


void Entity::move(const float dirX, const float dirY, const float deltaTime)
{
    if (movementComponent)
    {
        movementComponent->accelerateSprite(sf::Vector2f(dirX, dirY), deltaTime);
    }
}


void Entity::setPosition(const float posX, const float posY)
{
    if (hitboxComponent)
    {
        hitboxComponent->setPosition(posX, posY);
    }
    else
    {
        sprite.setPosition(posX, posY);
    }
}


const sf::Vector2f& Entity::getPosition() const
{
    if (hitboxComponent)
    {
        return hitboxComponent->getPosition();
    }
    return sprite.getPosition();
}


const sf::Vector2i Entity::getGridPosition() const
{
    if (hitboxComponent)
    {
        return sf::Vector2i(
            static_cast<sf::Vector2i>(hitboxComponent->getPosition()) / static_cast<int>(GRID_SIZE)
        );
    }
    return static_cast<sf::Vector2i>(sprite.getPosition()) / static_cast<int>(GRID_SIZE);
}


const sf::Vector2f Entity::getCenter() const
{
    if (hitboxComponent)
    {
        return hitboxComponent->getPosition() + 
                   sf::Vector2f(
                        hitboxComponent->getGlobalBounds().width / 2.f,
                        hitboxComponent->getGlobalBounds().height / 2.f
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
    if (hitboxComponent)
    {
        return hitboxComponent->getGlobalBounds();
    }
    return sprite.getGlobalBounds();
}


const sf::FloatRect Entity::getNextPositionBounds(const float deltaTime) const
{
    if (hitboxComponent && movementComponent)
    {
        return hitboxComponent->getNextPositionBounds(movementComponent->getVelocity() * deltaTime);
    }
    return sprite.getGlobalBounds();
}


void Entity::stopVelocity()
{
    if (movementComponent)
    {
        movementComponent->stopVelocity();
    }
}


void Entity::stopVelocityX()
{
    if (movementComponent)
    {
        movementComponent->stopVelocityX();
    }
}


void Entity::stopVelocityY()
{
    if (movementComponent)
    {
        movementComponent->stopVelocityY();
    }
}


void Entity::createMovementComponent(const float maxVelocity, 
                                     const float acceleration, 
                                     const float deceleration
                                     )
{
    movementComponent.reset(new MovementComponent(sprite, maxVelocity, acceleration, deceleration));
}


void Entity::createAnimationComponent(const sf::Texture& textureSheet)
{
    animationComponent.reset(new AnimationComponent(textureSheet, sprite));
}


void Entity::createHitboxComponent(const float offsetFromSpritePositionX,
                                   const float offsetFromSpritePositionY,
                                   const float hitboxWidth,
                                   const float hitboxHeight
                                   )
{
    hitboxComponent.reset(
        new HitboxComponent(
              sprite, 
              offsetFromSpritePositionX, 
              offsetFromSpritePositionY,
              hitboxWidth,
              hitboxHeight
        )
    );
}


void Entity::createAttributeComponent(const unsigned level, 
                                      const int hpMax, 
                                      const int damageMin, 
                                      const int damageMax
                                      )
{
    attributeComponent.reset(new AttributeComponent(level, hpMax, damageMin, damageMax));
}
