#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H


class ProgressBar
{
public:

                           ProgressBar();
    void                   create(const float posX,
                                  const float posY, 
                                  const float width, 
                                  const float height,
                                  const sf::Texture& barInnerTexture,
                                  const sf::Color& backColor = sf::Color::Transparent
                                  );
    void                   update(const int value, const int valueMax);
    void                   render(sf::RenderTarget& target);

    const sf::Vector2f&    getPosition() const;
    const sf::Vector2f&    getBackSize() const;

private:

    sf::Sprite             barInnerSprite;
    sf::RectangleShape     barBack;
};


#endif // PROGRESSBAR_H
