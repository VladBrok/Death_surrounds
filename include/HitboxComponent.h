#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include "SFML\Graphics.hpp"


class HitboxComponent: public sf::NonCopyable
{
public:

                        HitboxComponent(sf::Sprite& sprite,
                                        const float offsetFromSpriteOriginX,
                                        const float offsetFromSpriteOriginY,
                                        const float hitboxWidth,
                                        const float hitboxHeight
                                        );
    void                update();
    void                render(sf::RenderTarget& target);
    bool                checkIntersection(const sf::FloatRect& bounds) const;

private:

    sf::RectangleShape  hitbox;
    sf::Sprite&         sprite;
    float               offsetFromSpriteOriginX;
    float               offsetFromSpriteOriginY;

};


#endif // HITBOXCOMPONENT_H
