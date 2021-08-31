#ifndef INVENTORY_H
#define INVENTORY_H


class Item;
#include "TextTagSystem.h"


class Inventory
{
public:

                                       Inventory(const sf::RenderWindow& window, 
                                                 const sf::Texture& inventoryPanelBorderTexture
                                                 );
                                       
                                       ~Inventory();
    void                               update(const sf::Vector2f& itemPosition, 
                                              const sf::Vector2f& mousePosView,
                                              const sf::Vector2i& mousePosWindow,
                                              TextTagSystem& textTagSystem
                                              );
                          
    // Required view of the target must be set before calling this function
    void                               renderToView(sf::RenderTarget& target);
                          
    // Default view of the target must be set before calling this function
    void                               renderToWindow(sf::RenderTarget& target);
                                       
    bool                               addItem(Item* item);
    void                               removeItem(const int index);
    void                               setActiveItem(const int index);
    Item*                              getActiveItem() const;
    int                                getActiveItemIndex() const;

    // Returns the current number of items in the inventory (actual size)
    int                                getSize() const; 
                                       
    bool                               panelIsActive() const;
    void                               togglePanelHiddenStatus();
                          
private:                  
                          
    std::vector<std::unique_ptr<Item>> items; // The vector with a fixed size (empty positions are marked with nullptr)
    int                                actualSize;
    std::unique_ptr<Item>              activeItem; // This pointer holds a copy of the item
    int                                activeItemIndex;
                                       
    bool                               panelActive; // True if panel border contains mouse position related to window
    bool                               panelHidden;
    sf::Sprite                         panelBorder;
    sf::RectangleShape                 panelBackground;
    sf::RectangleShape                 selectedSlotBackground;
                                       
    void                               clear();                     
    void                               initInventoryPanel(const sf::RenderWindow& window, 
                                                          const sf::Texture& panelBorderTexture);
};


#endif // INVENTORY_H
