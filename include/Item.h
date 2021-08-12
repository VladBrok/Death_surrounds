#ifndef ITEM_H
#define ITEM_H


class Item
{
public:

                                  Item(const sf::Texture& texture, const sf::IntRect& textureRect = sf::IntRect());
    virtual                       ~Item() {};
    virtual void                  update(const sf::Vector2f& itemPosition, const sf::Vector2f& mousePosView) = 0;
    void                          render(sf::RenderTarget& target);
                                  
    // Returns the pointer to a new Item copied from the current one (memory must be freed by a caller using operator "delete")
    virtual Item*                 getClone() = 0;
                                  
    const sf::FloatRect           getGlobalBounds() const;
    const sf::Vector2f&           getPosition() const;
    const sf::IntRect&            getTextureRect() const;
    virtual const std::string     getName() const = 0;

    // Returns the default origin that was set after creation of the item
    const sf::Vector2f&           getDefaultOrigin() const;

    // Returns the default scale that was set after creation of the item
    const sf::Vector2f&           getDefaultScale() const;


    void                          setPosition(const float x, const float y);
    void                          setOrigin(const float x, const float y);
    void                          setScale(const float factorX, const float factorY);
    void                          setRotation(const float angle);

    virtual bool                  isWeapon() const;
    virtual bool                  isFood() const;
                                  
protected:                        
                                  
    const sf::Texture&            texture;
    sf::Sprite                    sprite;

    sf::Vector2f                  defaultOrigin;
    sf::Vector2f                  defaultScale;

    virtual void                  initDefaultOriginAndScale() = 0;
};


#endif // ITEM_H
