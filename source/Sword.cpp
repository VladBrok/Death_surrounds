#include "precompiled.h"
#include "Sword.h"
#include "Utils.h"


Sword::Sword(sf::Texture& texture, const int damage, const int damageMax)
    : Weapon(texture, damage, damageMax)
{
    initRange();
    initAttackTimerMax();

    sprite.setOrigin(
        sprite.getGlobalBounds().width / 2.f,
        sprite.getGlobalBounds().height
    );
}


void Sword::update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView)
{
    if (this->attackTimer.getElapsedTime().asMilliseconds() < attackTimerMax / 2)
    {
        sf::Vector2f swordPosOffset(utils::getNormalizedDirection(sprite.getPosition(), mousePosView));

        sprite.setPosition(
            weaponPosition.x + swordPosOffset.x * 10.f, 
            weaponPosition.y + swordPosOffset.y * 10.f
        );
    }
    else
    {
        sprite.setPosition(weaponPosition);

        utils::lookAt(sprite, mousePosView);
    }
}


void Sword::render(sf::RenderTarget& target)
{
    target.draw(sprite);
}


Sword* Sword::getClone()
{
    return new Sword(*this);
}


void Sword::initRange()
{
    range = 55.f;
}


void Sword::initAttackTimerMax()
{
    attackTimerMax = 200;
}