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
    void                saveToFile(const std::string& fileName);
    void                loadFromFile(const std::string& fileName);

    bool                addItem(Item*);
    void                removeItem(const int index);

    bool                isEmpty() const;
    int                 getSize() const;

    Item&               operator[](const int index);

private:

    std::list<Item*>    items;
    int                 maxNumberOfItems;

    void clear();

};


#endif // INVENTORY_H
