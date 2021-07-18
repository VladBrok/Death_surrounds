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
        sprite.getPosition().x + offsetFromSpritePositionX, 
        sprite.getPosition().y + offsetFromSpritePositionY
    );

    std::cout << "\n\n" << sprite.getPosition().x << ' ' << sprite.getPosition().y << '\n' 
              << sprite.getOrigin().x << ' ' << sprite.getOrigin().y << "\n\n";
}


void HitboxComponent::render(sf::RenderTarget& target)
{
    target.draw(hitbox);
}


bool HitboxComponent::checkIntersection(const sf::FloatRect& bounds) const
{
    return this->hitbox.getGlobalBounds().intersects(bounds);
}