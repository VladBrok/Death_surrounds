#include "precompiled.h"
#include "Sword.h"
#include "Utils.h"


Sword::Sword(sf::Texture& texture, const int damage, const int damageMax)
    : Weapon(texture, damage, damageMax)
{
    range = 50.f;

    sprite.setOrigin(
        sprite.getGlobalBounds().width / 2.f,
        sprite.getGlobalBounds().height
    );
}


void Sword::update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView)
{
    sprite.setPosition(weaponPosition);

    utils::lookAt(sprite, mousePosView);
}


void Sword::render(sf::RenderTarget& target)
{
    target.draw(sprite);
}


Sword* Sword::getClone()
{
    return new Sword(*this);
}