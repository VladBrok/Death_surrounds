#include "precompiled.h"
#include "Inventory.h"
#include "Item.h"
#include "constants.h"
#include "Utils.h"


Inventory::Inventory(const sf::RenderWindow& window, 
                     const sf::Texture& inventoryPanelBorderTexture
                     )
    : activeItem(nullptr), 
      activeItemIndex(0),
      actualSize(0),
      panelActive(false),
      panelHidden(false)
{   
    items.assign(INVENTORY_SIZE_MAX, nullptr);

    initInventoryPanel(window, inventoryPanelBorderTexture);
}


Inventory::~Inventory()
{
    clear();
}


void Inventory::update(const sf::Vector2f& itemPosition, 
                       const sf::Vector2f& mousePosView,
                       const sf::Vector2i& mousePosWindow,
                       TextTagSystem& textTagSystem
                       )
{
    if (!panelHidden)
    {
        // Selecting the new active item
        if (panelBorder.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) 
        {
            panelActive = true;
            int itemIndex = (int)(mousePosWindow.x - panelBorder.getPosition().x) / INVENTORY_SLOT_SIZE;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                activeItemIndex != itemIndex)
            {
                    setActiveItem(itemIndex);
                    selectedSlotBackground.setPosition(
                        panelBorder.getPosition().x + itemIndex * INVENTORY_SLOT_SIZE, 
                        panelBorder.getPosition().y
                    );

                    if (activeItem)
                    {
                        textTagSystem.addTextTag(
                            ITEM_NAME_TAG, 
                            sf::Vector2f(),
                            activeItem->getName()
                        );
                        textTagSystem.setBackElementPosition(
                            selectedSlotBackground.getPosition().x + selectedSlotBackground.getSize().x / 2.f - textTagSystem.getBackElementSize().x / 2.f,
                            selectedSlotBackground.getPosition().y - selectedSlotBackground.getSize().y / 1.3f
                        );
                    }
            }
        }
        else // if (!panelBorder.getGlobalBounds().contains(mousePosWindow))
        {
            panelActive = false;
        }
    }
    else // if (panelHidden)
    {
        panelActive = false;
    }


    if (activeItem)
    {
        activeItem->update(itemPosition, mousePosView);
    }
}


void Inventory::renderToView(sf::RenderTarget& target)
{
    if (activeItem)
    {
        activeItem->render(target);
    }
}


void Inventory::renderToWindow(sf::RenderTarget& target)
{
    if (!panelHidden)
    {
        target.draw(panelBackground);
        target.draw(selectedSlotBackground);
        target.draw(panelBorder);

        for (auto i = items.begin(); i != items.end(); ++i)
        {
            if (*i)
            {
                (*i)->render(target);
            }
        }
    }
}


bool Inventory::addItem(Item* pItem)
{
    assert(pItem != nullptr);

    int index = 0;

    // Searching an empty position
    while (items[index])
    {
        ++index;
    }

    if (index < (int)items.size())
    {
        items[index] = std::move(pItem->getClone());

        // Setting the item's transformation to properly place it to the inventory panel

        items[index]->setRotation(0.f);

        items[index]->setOrigin(0.f, 0.f);

        items[index]->setPosition(
            panelBorder.getPosition().x + INVENTORY_SLOT_SIZE * index,
            panelBorder.getPosition().y + INVENTORY_SLOT_OUTLINE_SIZE
        );

        items[index]->setScale(1.f, 1.f);
        items[index]->setScale(
            (INVENTORY_SLOT_SIZE) / items[index]->getGlobalBounds().width,
            (INVENTORY_SLOT_SIZE - INVENTORY_SLOT_OUTLINE_SIZE * 2) / items[index]->getGlobalBounds().height
        );


        if (index == activeItemIndex)
        {
            setActiveItem(index);
        }

        ++actualSize;

        return true;
    }
    return false;
}


void Inventory::removeItem(const int index)
{
    assert(index >= 0 && index < (int)items.size());

    if (index == activeItemIndex)
    {
        activeItem.reset(nullptr);
    }

    items[index].reset(nullptr);

    --actualSize;
}


void Inventory::setActiveItem(const int index)
{
    assert(index >= 0 && index < (int)items.size());

    if (items[index])
    {
        activeItem = std::move(items[index]->getClone());

        // Setting origin and scale of the item to default values
        activeItem->setOrigin(activeItem->getDefaultOrigin().x, activeItem->getDefaultOrigin().y);
        activeItem->setScale(activeItem->getDefaultScale().x, activeItem->getDefaultScale().y);

        activeItem->setPosition(0.f, 0.f);
    }
    else
    {
        activeItem.reset(nullptr);
    }
    activeItemIndex = index;
}


Item* Inventory::getActiveItem() const
{
    return activeItem.get();
}


int Inventory::getActiveItemIndex() const
{
    return activeItemIndex;
}


int Inventory::getSize() const
{
    return actualSize;
}


Item& Inventory::operator[](const int index)
{
    assert(index >= 0 && index < (int)items.size());

    if (!items[index])
    {
        throw std::runtime_error("ERROR in Inventory::operator[]: there is no item at that index");
    }

    return *items[index];
}


bool Inventory::panelIsActive() const
{
    return panelActive;
}


void Inventory::togglePanelHiddenStatus()
{
    panelHidden = !panelHidden;
}


void Inventory::clear()
{
    for (auto i = items.begin(); i != items.end(); ++i)
    {
        (*i).reset(nullptr);
    }

    activeItem.reset(nullptr);

    actualSize = 0;
}


void Inventory::initInventoryPanel(const sf::RenderWindow& window, 
                                   const sf::Texture& panelBorderTexture
                                   )
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
    panelBackground.setFillColor(sf::Color(70, 83, 83, 150));

    selectedSlotBackground.setSize(sf::Vector2f((float)INVENTORY_SLOT_SIZE, (float)INVENTORY_SLOT_SIZE));
    selectedSlotBackground.setFillColor(sf::Color(80, 80, 80, 155));
    selectedSlotBackground.setPosition(panelBorder.getPosition().x, panelBorder.getPosition().y);
}

