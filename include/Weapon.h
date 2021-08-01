#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"


class Weapon: public Item
{
public:

                    Weapon();
    virtual         ~Weapon();
    virtual void    update(const sf::Vector2f& weaponPosition, const sf::Vector2f& mousePosView) = 0;
    virtual void    render(sf::RenderTarget& target) = 0;

protected:

    sf::Texture     texture;
    sf::Sprite      sprite;
};


#endif // WEAPON_H
