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
    void                   accelerateSprite(const sf::Vector2f& movementDirection,
                                            const float deltaTime
                                            );
	
    // Decelerates and moves the sprite 
    void                   updateMovement(const float deltaTime);    
    
    const sf::Vector2f&    getVelocity() const;
    float                  getMaxVelocity() const;
    const std::string      getMovementState() const;

    // Resets the velocity to zero
    void                   stopVelocity();

    // Resets the velocity in the x-axis direction to zero
    void                   stopVelocityX();

    // Resets the velocity in the y-axis direction to zero
    void                   stopVelocityY();

private:

    sf::Sprite&            sprite;   

    float                  maxVelocity;
    float                  acceleration;
    float                  deceleration;
    sf::Vector2f           velocity;

    void                   decelerateAndCheckVelocityBounds(const float deltaTime);
    void                   deceleratePositiveVelocity(float& velocity, 
                                                      const float deltaTime
                                                      );
    void                   decelerateNegativeVelocity(float& velocity, 
                                                      const float deltaTime
                                                      );
};


#endif // MOVEMENT_COMPONENT_H
