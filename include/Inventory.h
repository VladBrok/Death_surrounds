#ifndef INVENTORY_H
#define INVENTORY_H


class Item;


class Inventory
{
public:

                        Inventory(const int maxNumberOfItems);
                        ~Inventory();
    void                update(const sf::Vector2f& itemPosition, const sf::Vector2f& mousePosView);
    void                render(sf::RenderTarget& target);

    bool                addItem(Item*);
    void                removeItem(const int index);
    void                setActiveItem(const int index);

    bool                isEmpty() const;
    int                 getSize() const;

    Item&               operator[](const int index);
    Item&               back();

private:

    std::list<Item*>    items;
    int                 maxNumberOfItems;
    Item*               pActiveItem;

    void                clear();

};


#endif // INVENTORY_H
