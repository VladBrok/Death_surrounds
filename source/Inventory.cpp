#include "precompiled.h"
#include "Inventory.h"
#include "Item.h"
#include "constants.h"
#include "Utils.h"


Inventory::Inventory(const int maxNumberOfItems, 
                     const sf::RenderWindow& window, 
                     const sf::Texture& inventoryPanelBorderTexture
                     )
    : maxNumberOfItems(maxNumberOfItems), 
      pActiveItem(nullptr), 
      previousActiveItemIndex(-1),
      previousInventorySize(0)
{
    assert(maxNumberOfItems > 0 && maxNumberOfItems <= INVENTORY_SIZE_MAX);
    
    initInventoryPanel(window, inventoryPanelBorderTexture);
}


Inventory::~Inventory()
{
    clear();
}


void Inventory::update(const sf::Vector2f& itemPosition, 
                       const sf::Vector2f& mousePosView,
                       const sf::Vector2i& mousePosWindow
                       )
{
    // Selecting the new active item
    if (panelBorder.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int itemIndex = (int)(mousePosWindow.x - panelBorder.getPosition().x) / INVENTORY_SLOT_SIZE;
        if (previousActiveItemIndex != itemIndex || previousInventorySize < (int)items.size())
        {
            setActiveItem(itemIndex);
            previousActiveItemIndex = itemIndex;
            previousInventorySize = (int)items.size();
        }
    }

    if (pActiveItem)
    {
        pActiveItem->update(itemPosition, mousePosView);
    }
}


void Inventory::renderToView(sf::RenderTarget& target)
{
    if (pActiveItem)
    {
        pActiveItem->render(target);
    }
}


void Inventory::renderToWindow(sf::RenderTarget& target)
{
    target.draw(panelBackground);
    target.draw(panelBorder);

    for (auto i = items.begin(); i != items.end(); ++i)
    {
        (*i)->render(target);
    }
}


bool Inventory::addItem(Item* pItem)
{
    assert(pItem != nullptr);

    if ((int)items.size() < maxNumberOfItems)
    {
        items.push_back(pItem->getClone());


        // Setting the item's origin, position and scale to properly place it to the inventory panel
        items.back()->setOrigin(0.f, 0.f);

        items.back()->setPosition(
            panelBorder.getPosition().x + INVENTORY_SLOT_SIZE * ((int)items.size() - 1),
            panelBorder.getPosition().y
        );

        items.back()->setScale(
            INVENTORY_SLOT_SIZE / items.back()->getGlobalBounds().width,
            INVENTORY_SLOT_SIZE / items.back()->getGlobalBounds().height
        );
        return true;
    }
    return false;
}


void Inventory::removeItem(const int index)
{
    assert(index >= 0 && index < (int)items.size());

    auto toRemove = items.begin();
    std::advance(toRemove, index);
    delete *toRemove;
    items.erase(toRemove);
}


void Inventory::setActiveItem(const int index)
{
    assert(index >= 0 && index < INVENTORY_SIZE_MAX);

    delete pActiveItem;

    if (index < (int)items.size())
    {
        pActiveItem = (this->operator[](index)).getClone();

        // Setting the origin and scale of the item to default values
        pActiveItem->setOrigin(pActiveItem->getDefaultOrigin().x, pActiveItem->getDefaultOrigin().y);
        pActiveItem->setScale(pActiveItem->getDefaultScale().x, pActiveItem->getDefaultScale().y);
    }
    else
    {
        pActiveItem = nullptr;
    }
}


Item* Inventory::getActiveItem() const
{
    return pActiveItem;
}


bool Inventory::isEmpty() const
{
    return items.empty();
}


int Inventory::getSize() const
{
    return (int)items.size();
}


Item& Inventory::operator[](const int index)
{
    assert(index >= 0 && index < (int)items.size());

    auto it = items.begin();
    std::advance(it, index);

    return **it;
}


Item& Inventory::back()
{
    if (items.empty())
    {
        throw std::runtime_error("ERROR in Inventory::back: vector of items is empty\n");
    }
    return *items.back();
}


void Inventory::clear()
{
    for (auto i = items.begin(); i != items.end(); ++i)
    {
        delete *i;
    }
    items.clear();

    delete pActiveItem;
    pActiveItem = nullptr;
}


void Inventory::initInventoryPanel(const sf::RenderWindow& window, const sf::Texture& panelBorderTexture)
{
    panelBorder.setTexture(panelBorderTexture);
    panelBorder.setPosition(
        window.getSize().x / 2 - panelBorder.getGlobalBounds().width / 2.f,
        window.getSize().y - (panelBorder.getGlobalBounds().height + utils::percentToPixels(15.f, window.getSize().y))
    );

    panelBackground.setPosition(panelBorder.getPosition());
    panelBackground.setSize(
        sf::Vector2f(
            panelBorder.getGlobalBounds().width, 
            panelBorder.getGlobalBounds().height
        )
    );
    panelBackground.setFillColor(sf::Color(78, 91, 91, 150));
}

