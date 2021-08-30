#include "precompiled.h"
#include "DropDownList.h"
#include "Button.h"


DropDownList::DropDownList(const float posX,
                           const float posY,
                           const float elementWidth,
                           const float elementHeight,
                           sf::Font& font,
                           const std::vector<std::string>& list,
                           const int activeElementIndex
                           )
    : font(font), showList(false), hoveredElementIndex(-1)
{
    assert(activeElementIndex >= 0 && activeElementIndex < (int)list.size());

    for (int i = 0; i < (int)list.size(); ++i)
    {
        if (i == 0) // Creating active list element
        {
           std::unique_ptr<Button> button(
               new Button(
                     posX, posY + elementHeight * i,
                     elementWidth, elementHeight,
                     font, 
                     list[i],
                     sf::Color::White,
                     sf::Color::White,
                     sf::Color::White,
                     sf::Color(70, 70, 70, 200),
                     sf::Color(40, 40, 40, 200),
                     sf::Color(40, 40, 40, 200),
                     sf::Color(200, 200, 200, 200),
                     sf::Color(220, 220, 220, 230),
                     sf::Color::White
               )
           );
           listElements.push_back(std::move(button));
        }
        else // Creating regular list element
        {
           std::unique_ptr<Button> button(
               new Button(
                    posX, posY + elementHeight * i,
                    elementWidth, elementHeight,
                    font, 
                    list[i],
                    sf::Color::White,
                    sf::Color::White,
                    sf::Color::White,
                    sf::Color(100, 100, 100, 180),
                    sf::Color(150, 150, 150, 200),
                    sf::Color(40, 40, 40, 200)
               )
           );
           listElements.push_back(std::move(button));
        }
    }

    if (activeElementIndex != 0)
    {
        swapListElementTexts(0, activeElementIndex);
    }
}


void DropDownList::processEvent(const sf::Event& event,
                                const sf::Vector2i& mousePosWindow
                                )
{
    // Processing only title element
    if (!showList) 
    {
        listElements[0]->processEvent(event, mousePosWindow);

        if (listElements[0]->isPressed())
        {
            handleListElementPress(0);
            return;
        }
    }

    // Processing and resetting hovered element
    else if (hoveredElementIndex != -1) 
    {
        listElements[hoveredElementIndex]->processEvent(event, mousePosWindow);

        if (listElements[hoveredElementIndex]->isPressed())
        {
            handleListElementPress(hoveredElementIndex);
            if (hoveredElementIndex != 0)
            {
                hoveredElementIndex = -1;
            }
        }

        else if (!listElements[hoveredElementIndex]->isHovered())
        {
            hoveredElementIndex = -1;
        }
    }


    // Searching for new hovered element
    if (showList && hoveredElementIndex == -1) 
    {
        for (int i = 0; (i < (int)listElements.size()) && hoveredElementIndex == -1 && showList; ++i)
        {
            listElements[i]->processEvent(event, mousePosWindow);

            if (listElements[i]->isHovered())
            {
                hoveredElementIndex = i;
            }
            else if (listElements[i]->isPressed())
            {
                handleListElementPress(i);
            }
        }
    }
}


void DropDownList::render(sf::RenderTarget& target)
{
    listElements[0]->render(target);

    if (showList)
    {
        for (int i = 1; i < (int)listElements.size(); ++i)
        {
            listElements[i]->render(target);
        }
    }
}


const std::string& DropDownList::getActiveElementText() const
{
    return listElements[0]->getText();
}


void DropDownList::swapListElementTexts(const int element1_index, const int element2_index)
{
    std::string tmp = listElements[element1_index]->getText();

    listElements[element1_index]->setText(listElements[element2_index]->getText());

    listElements[element2_index]->setText(tmp);
}


void DropDownList::handleListElementPress(const int elementIndex)
{
    if (elementIndex == 0)
    {
        showList = !showList;
    }
    else
    {
        showList = false;
        swapListElementTexts(0, elementIndex);
    }
}