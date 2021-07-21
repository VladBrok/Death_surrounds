#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H


class MovementComponent: public sf::NonCopyable
{
public:

                             MovementComponent(sf::Sprite& sprite, 
                                               const float maxVelocity,
                                               const float acceleration, 
                                               const float deceleration
                                               );
    void                     accelerateSprite(const sf::Vector2f& movementDirection, const float deltaTime);
    const sf::Vector2f&      getVelocity() const;
    float                    getMaxVelocity() const;
    void                     updateMovement(const float deltaTime); // Decelerates and moves the sprite
    const std::string        getMovementState() const; // FIXME: Maybe should create enum and return it

private:

    sf::Sprite&              sprite;   

    float                    maxVelocity;
    float                    acceleration;
    float                    deceleration;
    sf::Vector2f             velocity;

    void                     decelerateSpriteAndCheckVelocityBounds(const float deltaTime);

};


#endif // MOVEMENT_COMPONENT_H
