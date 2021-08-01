#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H


class ProgressBar
{
public:

                            ProgressBar();
    void                    create(const float posX,
                                   const float posY, 
                                   const float width, 
                                   const float height,
                                   sf::Font& font,
                                   const sf::Color& innerColor,
                                   const sf::Color& backColor = sf::Color::Transparent,
                                   const bool centerText = false,
                                   const std::string& barTextStr = ""
                                   );
    void                    update(const int value, const int valueMax);
    void                    render(sf::RenderTarget& target);

    const sf::Vector2f&     getPosition() const;
    const sf::Vector2f&     getBackSize() const;
    void                    setTextString(const std::string& string);

private:

    sf::RectangleShape      barBack;
    sf::RectangleShape      barInner;
    sf::Text                barText;

};


#endif // PROGRESSBAR_H
