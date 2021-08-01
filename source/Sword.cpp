#include "precompiled.h"
#include "Sword.h"


Sword::Sword()
{
    texture.loadFromFile("Resources\\Images\\Items\\Weapon\\sword.png");
    sprite.setTexture(texture);

    sprite.setOrigin(
        sprite.getGlobalBounds().width / 2.f,
        sprite.getGlobalBounds().height
    );
}


void Sword::update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView)
{
    sprite.setPosition(weaponPosition);

    // Making the weapon point towards the mouse
    sf::Vector2f direction(mousePosView - sprite.getPosition());

    const float dirLength = std::sqrtf(direction.x * direction.x + direction.y * direction.y);

    direction /= dirLength; // Normalizing the direction vector

    const float PI = 3.14159265358979323846f;
    const float degree = std::atan2f(direction.y, direction.x) * 180 / PI;
    sprite.setRotation(degree + 90.f);
}


void Sword::render(sf::RenderTarget& target)
{
    target.draw(sprite);
}