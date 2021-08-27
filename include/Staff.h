#ifndef STAFF_H
#define STAFF_H


#include "RangedWeapon.h"
class Projectile;


class Staff: public RangedWeapon
{
public:
                      
                                 Staff(const sf::Texture& weaponTexture,
                                       const sf::Texture& unloadedWeaponTexture,
                                       const sf::Texture& projectileTexture,
                                       const int projectileDamageMin,
                                       const int projectileDamageMax, 
                                       const sf::IntRect& textureRect = sf::IntRect()
                                       );
    virtual void                 update(const sf::Vector2f& weaponPosition, 
                                        const sf::Vector2f& mousePosView);
    virtual Staff*               getClone();
    virtual const std::string    getName() const;
    virtual Projectile*          allocateNewProjectile(const sf::Vector2f& movementDir, 
                                                       const sf::Vector2f& position);
                      
private:

    const sf::Texture*           pUnloadedWeaponTexture;
    const sf::Texture*           pProjectileTexture;
    float                        projectileLifetimeInSeconds;
    float                        projectileSpeed;
                    
    virtual void                 initRange();
    virtual void                 initAttackTimerMax();
    virtual void                 initDefaultOriginAndScale();
};


#endif // STAFF_H
