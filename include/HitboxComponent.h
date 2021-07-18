#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include "SFML\Graphics.hpp"
#include <iostream>


class HitboxComponent: public sf::NonCopyable
{
public:

                        HitboxComponent(sf::Sprite& sprite,
                                        const float offsetFromSpritePositionX,
                                        const float offsetFromSpritePositionY,
                                        const float hitboxWidth,
                                        const float hitboxHeight
                                        );
    void                update();
    void                render(sf::RenderTarget& target);
    bool                checkIntersection(const sf::FloatRect& bounds) const;

private:

    sf::RectangleShape  hitbox;
    sf::Sprite&         sprite;
    float               offsetFromSpritePositionX;
    float               offsetFromSpritePositionY;

};


#endif // HITBOXCOMPONENT_H
