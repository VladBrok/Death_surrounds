#ifndef ITEM_H
#define ITEM_H


class Item
{
public:

                           Item(const sf::Texture& texture, const sf::IntRect& textureRect = sf::IntRect());
    virtual                ~Item() {};
    virtual void           update(const sf::Vector2f& itemPosition, const sf::Vector2f& mousePosView) = 0;
    void                   render(sf::RenderTarget& target);
                           
    // Returns the pointer to a new Item copied from the current one (memory must be freed by a caller using operator "delete")
    virtual Item*          getClone() = 0;
                           
    const sf::FloatRect    getGlobalBounds() const;
    void                   setPosition(const float x, const float y);
                           
protected:                 
                           
    const sf::Texture&     texture;
    sf::Sprite             sprite;
};


#endif // ITEM_H
