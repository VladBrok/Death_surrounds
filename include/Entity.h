#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"


class Entity
{
public:

                        Entity(const sf::Texture& texture);
    virtual             ~Entity();
    void                createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void                createAnimationComponent(sf::Texture& textureSheet, sf::Sprite& sprite);
    void                setPosition(const float posX, const float posY);
    virtual void        update(const float deltaTime);
    virtual void        render(sf::RenderTarget* target);
    virtual void        move(const float dirX, const float dirY, const float deltaTime);

protected:

    sf::Sprite          sprite;
    MovementComponent*  pMovementComponent; // Entity is movable if pMovemenComponent != nullptr
    AnimationComponent* pAnimationComponent;
};


#endif // ENTITY_H
