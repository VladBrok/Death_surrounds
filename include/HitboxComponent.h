#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include "SFML\Graphics.hpp"


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
    const bool          checkIntersection(const sf::FloatRect& bounds) const;

private:

    sf::RectangleShape  hitbox;
    sf::Sprite&         sprite; // FIXME: Maybe should make it const
    float               offsetFromSpritePositionX;
    float               offsetFromSpritePositionY;

};


#endif // HITBOXCOMPONENT_H
