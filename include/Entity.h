#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"


class Entity
{
public:

                          Entity(const sf::Texture& texture);
    virtual               ~Entity();
                          
    virtual void          update(const float deltaTime) = 0;
    virtual void          render(sf::RenderTarget& target);
    virtual void          move(const float dirX, const float dirY, const float deltaTime);
                          
    void                  setPosition(const float posX, const float posY);
    const sf::Vector2f&   getPosition() const;
    const sf::Vector2i    getGridPosition() const;
    const sf::FloatRect   getGlobalBounds() const;
    const sf::FloatRect&  getNextPositionBounds(const float deltaTime) const;

    void                  stopVelocity();
    void                  stopVelocityX();
    void                  stopVelocityY();
                        
protected:              
                        
    sf::Sprite            sprite;
                         
    /*
        If the pointer to a component is nullptr, then
        this component is missing.
    */
    MovementComponent*    pMovementComponent;
    AnimationComponent*   pAnimationComponent;
    HitboxComponent*      pHitboxComponent;
    AttributeComponent*   pAttributeComponent;
                          
    void                  createMovementComponent(const float maxVelocity, 
                                                  const float acceleration, 
                                                  const float deceleration
                                                  );
    void                  createAnimationComponent(sf::Texture& textureSheet);
    void                  createHitboxComponent(const float offsetFromSpritePositionX,
                                                const float offsetFromSpritePositionY,
                                                const float hitboxWidth,
                                                const float hitboxHeight
                                                );
    void                  createAttributeComponent(const unsigned level);
};


#endif // ENTITY_H
