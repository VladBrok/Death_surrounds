#ifndef ITEM_H
#define ITEM_H


class Item
{
public:

                    Item(sf::Texture& texture);
    virtual         ~Item() {};
    virtual void    update(const sf::Vector2f& itemPosition, const sf::Vector2f& mousePosView) = 0;
    virtual void    render(sf::RenderTarget& target) = 0;

    // Returns the pointer to a new Item copied from the current one (memory must be freed by a caller using operator "delete")
    virtual Item*   getClone() = 0;

protected:

    sf::Texture&    texture;
    sf::Sprite      sprite;
};


#endif // ITEM_H
