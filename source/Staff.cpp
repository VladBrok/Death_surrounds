#include "precompiled.h"
#include "Staff.h"
#include "Utils.h"
#include "Projectile.h"


Staff::Staff(const sf::Texture& weaponTexture,
             const sf::Texture& unloadedWeaponTexture,
             const sf::Texture& projectileTexture,
             const int projectileDamageMin, 
             const int projectileDamageMax,
             const sf::IntRect& textureRect
             )
    : RangedWeapon(weaponTexture, projectileTexture, projectileDamageMin, projectileDamageMax, textureRect),
      pProjectileTexture(&projectileTexture),
      pUnloadedWeaponTexture(&unloadedWeaponTexture)
{
    initRange();
    initAttackTimerMax();
    initDefaultOriginAndScale();
    sprite.setOrigin(defaultOrigin);


    projectileLifetimeInSeconds = 1.5f;
    projectileSpeed             = 310.f;
}


void Staff::update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView)
{
    sprite.setPosition(weaponPosition);
    utils::lookAt(sprite, mousePosView);

    if (attackTimer.getElapsedTime().asMilliseconds() < attackTimerMax)
    {
        sprite.setTexture(*pUnloadedWeaponTexture);
    }
    else
    {
        sprite.setTexture(*pTexture);
    }
}


Staff* Staff::getClone()
{
    return new Staff(*this);
}


const std::string Staff::getName() const
{
    return "Warlock's staff";
}


void Staff::initRange()
{
    range = 350.f;
}


void Staff::initAttackTimerMax()
{
    attackTimerMax = 1300;
}


void Staff::initDefaultOriginAndScale()
{
    defaultOrigin.x = sprite.getGlobalBounds().width / 2.f;
    defaultOrigin.y = sprite.getGlobalBounds().height;
    
    defaultScale.x = defaultScale.y = 1.f;
}


// FIXME: use unique_ptr !!
Projectile* Staff::allocateNewProjectile(const sf::Vector2f& movementDir, const sf::Vector2f& position)
{
    return new Projectile(
                   *pProjectileTexture, 
                    position,
                    movementDir, 
                    projectileSpeed,
                    projectileLifetimeInSeconds,
                    damageMin, 
                    damageMax
               );
}