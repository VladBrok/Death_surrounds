#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "SFML/Graphics.hpp"


class MovementComponent
{
public:

    MovementComponent(const float maxVelocity);
    void setVelocity(const sf::Vector2f& movementDirection);
    const sf::Vector2f& getVelocity() const;

private:

    float maxVelocity;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f deceleration;

};


#endif // MOVEMENT_COMPONENT_H
