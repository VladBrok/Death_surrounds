#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"


class Entity: public sf::NonCopyable
{
public:

    explicit                            Entity(const sf::Texture& texture);
    virtual                             ~Entity();
                                        
    virtual void                        render(sf::RenderTarget& target, 
                                               sf::Shader* pShader = nullptr,
                                               const sf::Vector2f& shaderLightPosition = sf::Vector2f(),
                                               const bool showHitbox = false
                                               );
    virtual void                        move(const float dirX, const float dirY, const float deltaTime);                       
    void                                setPosition(const float posX, const float posY);
                                        
    const sf::Vector2f&                 getPosition() const;
    const sf::Vector2i                  getGridPosition() const;
    const sf::Vector2f                  getCenter() const;
    const sf::Vector2i                  getGridPositionCenter() const;
                                        
    const sf::FloatRect                 getGlobalBounds() const;
    const sf::FloatRect                 getNextPositionBounds(const float deltaTime) const;
                                        
    void                                stopVelocity();
    void                                stopVelocityX();
    void                                stopVelocityY();
                                        
protected:                              
                                        
    sf::Sprite                          sprite;
    const sf::Texture&                  texture;
                            
    /*                      
        If the pointer to a component is nullptr, then
        this component is missing.
    */                      
    std::unique_ptr<MovementComponent>  movementComponent;
    std::unique_ptr<AnimationComponent> animationComponent;
    std::unique_ptr<HitboxComponent>    hitboxComponent;
    std::unique_ptr<AttributeComponent> attributeComponent;
                            
    void                                createMovementComponent(const float maxVelocity, 
                                                                const float acceleration, 
                                                                const float deceleration
                                                                );
    void                                createAnimationComponent(const sf::Texture& textureSheet);
    void                                createHitboxComponent(const float offsetFromSpritePositionX,
                                                              const float offsetFromSpritePositionY,
                                                              const float hitboxWidth,
                                                              const float hitboxHeight
                                                              );
    void                                createAttributeComponent(const unsigned level,
                                                                 const int hpMax, 
                                                                 const int damageMin, 
                                                                 const int damageMax
                                                                 );
};


#endif // ENTITY_H
