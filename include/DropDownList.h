#ifndef DROPDOWNLIST_H
#define DROPDOWNLIST_H

#include "Button.h"


class DropDownList: public sf::NonCopyable
{
public:

                            DropDownList(const float posX,
                                         const float posY,
                                         const float elementWidth,
                                         const float elementHeight,
                                         sf::Font& font,
                                         const std::vector<std::string>& list,
                                         const int activeElementIndex = 0
                                         );
                            ~DropDownList();

    void                    processEvent(const sf::Event& event,
                                              const sf::Vector2f& mousePosition
                                              );
    void                    render(sf::RenderTarget& target);
    const std::string&      getActiveElementText() const;

private:

    sf::Font&               font;
    std::vector<Button*>    listElements;
    bool                    showList;
    int                     hoveredElementIndex; // Used to prevent the selection of several list elements simultaneously

    void                    swapListElementTexts(const int element1_index, const int element2_index);
    void                    handleListElementPress(const int elementIndex);
    
};


#endif // DROPDOWNLIST_H
