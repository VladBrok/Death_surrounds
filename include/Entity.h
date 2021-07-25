#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"


class Entity
{
public:

                        Entity(const sf::Texture& texture);
    virtual             ~Entity();

    virtual void        update(const float deltaTime);
    virtual void        render(sf::RenderTarget& target);
    virtual void        move(const float dirX, const float dirY, const float deltaTime);
    void                setPosition(const float posX, const float posY);
    const sf::Vector2f& getPosition() const;

protected:

    sf::Sprite          sprite;
                        
    /*
        If the pointer to a component is nullptr, then
        this component is missing.
    */
    MovementComponent*  pMovementComponent;
    AnimationComponent* pAnimationComponent;
    HitboxComponent*    pHitboxComponent;

    void                createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void                createAnimationComponent(sf::Texture& textureSheet);
    void                createHitboxComponent(const float offsetFromSpritePositionX,
                                              const float offsetFromSpritePositionY,
                                              const float hitboxWidth,
                                              const float hitboxHeight
                                              );
};


#endif // ENTITY_H
