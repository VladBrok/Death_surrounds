#ifndef TEXTURE_SELECTOR_H
#define TEXTURE_SELECTOR_H


class TextureSelector
{
public:

                            TextureSelector(const float posX, 
                                            const float posY, 
                                            const float width, 
                                            const float height,
                                            const sf::Texture& textureSheet
                                            );

    void                    processEvent(const sf::Event& event, const sf::Vector2i& mousePosWindow);
    void                    render(sf::RenderTarget& target);

    bool                    isActive() const;
    const sf::IntRect&      getTextureRect() const;

private:

    const sf::Texture&      textureSheet;
    sf::IntRect             textureRect;
    sf::RectangleShape      selector;
    sf::Sprite              sheet;
    sf::RectangleShape      bounds;
    bool                    active; // Acitve is true when the texture selector contains a mouse position

};


#endif // TEXTURE_SELECTOR_H
