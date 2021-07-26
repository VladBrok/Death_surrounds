#include "precompiled.h"
#include "HitboxComponent.h"


HitboxComponent::HitboxComponent(sf::Sprite& sprite,
                                 const float offsetFromSpritePositionX,
                                 const float offsetFromSpritePositionY,
                                 const float hitboxWidth,
                                 const float hitboxHeight
                                 )
    : sprite(sprite),
      offsetFromSpritePositionX(offsetFromSpritePositionX),
      offsetFromSpritePositionY(offsetFromSpritePositionY),
      hitbox(sf::Vector2f(hitboxWidth, hitboxHeight)),
      hitboxNextPosition(0.f, 0.f, hitboxWidth, hitboxHeight)
{
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineThickness(-1.f);
    hitbox.setOutlineColor(sf::Color::Green);
 
    update();
}


void HitboxComponent::update()
{
    hitbox.setPosition(
        sprite.getPosition().x + offsetFromSpritePositionX, 
        sprite.getPosition().y + offsetFromSpritePositionY
    );
}


void HitboxComponent::render(sf::RenderTarget& target)
{
    target.draw(hitbox);
}


bool HitboxComponent::intersects(const sf::FloatRect& bounds) const
{
    return this->hitbox.getGlobalBounds().intersects(bounds);
}


void HitboxComponent::setPosition(const float posX, const float posY)
{
    hitbox.setPosition(posX, posY);

    sprite.setPosition(
        posX - offsetFromSpritePositionX,
        posY - offsetFromSpritePositionY
    );
}


const sf::Vector2f& HitboxComponent::getPosition() const
{
    return hitbox.getPosition();
}


const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
    return hitbox.getGlobalBounds();
}


const sf::FloatRect& HitboxComponent::getNextPositionBounds(const sf::Vector2f& velocity)
{
    hitboxNextPosition.left = hitbox.getPosition().x + velocity.x;
    hitboxNextPosition.top  = hitbox.getPosition().y + velocity.y;

    return hitboxNextPosition;
}