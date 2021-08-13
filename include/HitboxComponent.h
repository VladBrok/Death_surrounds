#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H


class HitboxComponent: public sf::NonCopyable
{
public:

                            HitboxComponent(sf::Sprite& sprite,
                                            const float offsetFromSpritePositionX,
                                            const float offsetFromSpritePositionY,
                                            const float hitboxWidth,
                                            const float hitboxHeight
                                            );
    void                    update();
    void                    render(sf::RenderTarget& target);
                            
    bool                    intersects(const sf::FloatRect& bounds) const;
    void                    setPosition(const float posX, const float posY);
    const sf::Vector2f&     getPosition() const;
    const sf::FloatRect     getGlobalBounds() const;
    const sf::FloatRect&    getNextPositionBounds(const sf::Vector2f& velocity);
                            
private:                    
                            
    sf::RectangleShape      hitbox;
    sf::Sprite&             sprite;
    float                   offsetFromSpritePositionX;
    float                   offsetFromSpritePositionY;
    sf::FloatRect           hitboxNextPosition;

};


#endif // HITBOXCOMPONENT_H
