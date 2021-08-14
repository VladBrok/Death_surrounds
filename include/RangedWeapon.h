#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "Weapon.h"
class Projectile;


class RangedWeapon: public Weapon
{
public:

                           RangedWeapon(const sf::Texture& texture, 
                                        const sf::Texture& projectileTexture,
                                        const int projectileDamageMin,
                                        const int projectileDamageMax, 
                                        const sf::IntRect& textureRect = sf::IntRect()
                                        );
    virtual WeaponType     getWeaponType() const;

    // Returns the new projectile. Allocated memeory must be freed by a caller
    virtual                Projectile* allocateNewProjectile(const sf::Vector2f& movementDir, const sf::Vector2f& position) = 0;
};


#endif // RANGEDWEAPON_H