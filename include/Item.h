#ifndef ITEM_H
#define ITEM_H


class Item
{
public:

    explicit                      Item(const sf::Texture& texture, 
                                       const sf::IntRect& textureRect = sf::IntRect()
                                       );
    virtual                       ~Item() {};
    virtual void                  update(const sf::Vector2f& itemPosition, 
                                         const sf::Vector2f& mousePosView) = 0;
    virtual void                  render(sf::RenderTarget& target);
                                  
    // Returns the unique pointer to a new Item copied from the current one
    virtual std::unique_ptr<Item> getClone() = 0;
                                 
    const sf::FloatRect           getGlobalBounds() const;
    const sf::Vector2f&           getPosition() const;
    const sf::IntRect&            getTextureRect() const;
    virtual const std::string     getName() const = 0;
    const sf::Vector2f&           getDefaultOrigin() const;
    const sf::Vector2f&           getDefaultScale() const;
                                  
    void                          setPosition(const float x, const float y);
    void                          setOrigin(const float x, const float y);
    void                          setScale(const float factorX, const float factorY);
    void                          setRotation(const float angle);
                                  
    virtual bool                  isWeapon() const;
    virtual bool                  isFood() const;
                                  
protected:                        
                                  
    const sf::Texture*            pTexture;
    sf::Sprite                    sprite;
                                  
    sf::Vector2f                  defaultOrigin;
    sf::Vector2f                  defaultScale;
                                  
    virtual void                  initDefaultOriginAndScale() = 0;
};


#endif // ITEM_H
