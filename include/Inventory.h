#ifndef INVENTORY_H
#define INVENTORY_H


class Item;


class Inventory
{
public:

                          Inventory(const int maxNumberOfItems,
                                    const sf::RenderWindow& window, 
                                    const sf::Texture& inventoryPanelBorderTexture
                                    );
                          
                          ~Inventory();
    void                  update(const sf::Vector2f& itemPosition, 
                                 const sf::Vector2f& mousePosView,
                                 const sf::Vector2i& mousePosWindow
                                 );
                          
    // Required view of   the target must be set before calling this function
    void                  renderToView(sf::RenderTarget& target);
                          
    // Default view of t  he target must be set before calling this function
    void                  renderToWindow(sf::RenderTarget& target);
                          
    bool                  addItem(Item*);
    void                  removeItem(const int index);
    void                  setActiveItem(const int index);
    Item*                 getActiveItem() const;
                          
    bool                  isEmpty() const;
    int                   getSize() const;
                          
    Item&                 operator[](const int index);
    Item&                 back();
                          
private:                  
                          
    std::list<Item*>      items;
    int                   maxNumberOfItems;
    Item*                 pActiveItem;
    int                   previousActiveItemIndex;
    int                   previousInventorySize;
                          
    sf::Sprite            panelBorder;
    sf::RectangleShape    panelBackground;
                          
    void                  clear();
                          
    void                  initInventoryPanel(const sf::RenderWindow& window, const sf::Texture& panelBorderTexture);

};


#endif // INVENTORY_H
