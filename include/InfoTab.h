#ifndef INFOTAB_H
#define INFOTAB_H


class InfoTab
{
public:

                          InfoTab();
    virtual void          update() = 0;
    virtual void          render(sf::RenderTarget& target);

    void                  hide();
    void                  show();
    bool                  isHidden() const;

    // Sets the "hidden" status to true if it's false and vice versa
    void                  toggle();

protected:

    sf::RectangleShape    tabBackground;
    sf::Text              tabText;

    virtual void          initInfoTab(const sf::RenderWindow& window, const sf::Font& font) = 0;

private:

    bool                  hidden;

};


#endif // INFOTAB_H
