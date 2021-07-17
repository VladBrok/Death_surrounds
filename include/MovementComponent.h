#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "SFML/Graphics.hpp"


class MovementComponent: public sf::NonCopyable
{
public:

                            MovementComponent(sf::Sprite& sprite, const float maxVelocity,
                                              const float acceleration, const float deceleration
                                              );
    void                    accelerateSprite(const sf::Vector2f& movementDirection, const float deltaTime);
    const sf::Vector2f&     getVelocity() const;
    void                    updateMovement(const float deltaTime); // Decelerates and moves the sprite
    const bool              isIdle() const;

private:

    sf::Sprite&             sprite;   

    float                   maxVelocity;
    float                   acceleration;
    float                   deceleration;
    sf::Vector2f            velocity;

    void                    decelerateSpriteAndCheckVelocityBounds(const float deltaTime);

};


#endif // MOVEMENT_COMPONENT_H
