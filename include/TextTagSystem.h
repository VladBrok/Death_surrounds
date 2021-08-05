#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H


enum PresetTextTagId
{
    DEFAULT_TAG,
    EXPERIENCE_TAG,
    DAMAGE_TAG,
    NUMBER_OF_PRESET_TAGS
};


class TextTagSystem: public sf::NonCopyable
{
public:

                TextTagSystem(const sf::Font& font);

    void        update(const float deltaTime);
    void        render(sf::RenderTarget& target);

    void        addTextTag(const int presetTagId, const sf::Vector2f& position, const std::string& text);
    void        addTextTag(const int presetTagId, const sf::Vector2f& position, const int text);

private:


    class TextTag
    {
    public:

        sf::Text    sfmlText;
        float       movementDirX;
        float       movementDirY;
        float       lifetime;
        float       speed;


        TextTag(const sf::Font& font, 
                const std::string& text, 
                const float posX, 
                const float posY, 
                const float movementDirX, 
                const float movementDirY, 
                const sf::Color& textColor, 
                const unsigned charSize, 
                const float lifetime, 
                const float speed
                )
                : movementDirX(movementDirX),
                  movementDirY(movementDirY),
                  lifetime(lifetime),
                  speed(speed)
        {
            sfmlText.setFont(font);
            sfmlText.setString(text);
            sfmlText.setPosition(posX, posY);
            sfmlText.setColor(textColor);
            sfmlText.setCharacterSize(charSize);
        }

        void update(const float deltaTime)
        {
            if (lifetime > 0.f)
            {
                lifetime -= deltaTime * (1000.f / 16.f);

                sfmlText.move(movementDirX * speed * deltaTime, movementDirY * speed * deltaTime);
            }
        }

        void render(sf::RenderTarget& target)
        {
            target.draw(sfmlText);
        }

        inline bool isExpired() const
        {
            return lifetime <= 0.f;
        }

        void setText(const std::string& text)
        {
            sfmlText.setString(text);
        }

        void setPosition(const sf::Vector2f& position)
        {
            sfmlText.setPosition(position);
        }

    };


    const sf::Font&                                   font;
    std::list< std::shared_ptr<TextTag> >             tags;
    std::unordered_map<int, std::shared_ptr<TextTag>> presetTags;

    void                                              initPresetTags();
    void                                              addTag(const int presetTagId, 
                                                             const sf::Vector2f& position, 
                                                             const std::string& text
                                                             );
};


#endif // TEXTTAGSYSTEM_H

