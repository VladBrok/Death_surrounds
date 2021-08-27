#include "precompiled.h"
#include "RangedWeapon.h"


RangedWeapon::RangedWeapon(const sf::Texture& texture, 
                           const sf::Texture&,
                           const int projectileDamageMin,
                           const int projectileDamageMax, 
                           const sf::IntRect& textureRect
                           )
                           : Weapon(texture, projectileDamageMin, projectileDamageMax, textureRect)
{
}


WeaponType RangedWeapon::getWeaponType() const
{
    return RANGED_WEAPON;
}
