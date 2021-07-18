#include "HitboxComponent.h"


HitboxComponent::HitboxComponent(sf::Sprite& sprite,
                                 const float offsetFromSpriteOriginX,
                                 const float offsetFromSpriteOriginY,
                                 const float hitboxWidth,
                                 const float hitboxHeight
                                 )
    : sprite(sprite),
      offsetFromSpriteOriginX(offsetFromSpriteOriginX),
      offsetFromSpriteOriginY(offsetFromSpriteOriginY),
      hitbox(sf::Vector2f(hitboxWidth, hitboxHeight))
{
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineThickness(1.f);
    hitbox.setOutlineColor(sf::Color::Green);

    update();
}


void HitboxComponent::update()
{
    hitbox.setPosition(
        sprite.getPosition().x + offsetFromSpriteOriginX, 
        sprite.getPosition().y + offsetFromSpriteOriginY
    );
}


void HitboxComponent::render(sf::RenderTarget& target)
{
    target.draw(hitbox);
}


bool HitboxComponent::checkIntersection(const sf::FloatRect& bounds) const
{
    return this->hitbox.getGlobalBounds().intersects(bounds);
}