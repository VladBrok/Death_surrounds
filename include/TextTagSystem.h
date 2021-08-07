#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H


enum PresetTextTagId
{
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

    template <class T>
    void        addTextTag(const int presetTagId, 
                           const sf::Vector2f& position, 
                           const T& text, 
                           const std::string& prefix = "", 
                           const std::string& postfix = ""
                           );

private:


    class TextTag
    {
    public:

        sf::Text    sfmlText;
        float       movementDirX;
        float       movementDirY;
        float       lifetime;
        float       speed;
        int         fadeValue;


        TextTag(const sf::Font& font, 
                const std::string& text, 
                const float posX, 
                const float posY, 
                const float movementDirX, 
                const float movementDirY, 
                const sf::Color& textColor, 
                const unsigned charSize, 
                const float lifetime, 
                const float speed,
                const int fadeValue
                )
                : movementDirX(movementDirX),
                  movementDirY(movementDirY),
                  lifetime(lifetime),
                  speed(speed),
                  fadeValue(fadeValue)
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

                if (fadeValue > 0 && sfmlText.getColor().a >= fadeValue)
                {
                    sfmlText.setColor(
                        sf::Color(
                            sfmlText.getColor().r,
                            sfmlText.getColor().g,
                            sfmlText.getColor().b,
                            sfmlText.getColor().a - fadeValue
                        )
                    );
                }
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


template <class T>
void TextTagSystem::addTextTag(const int presetTagId, 
                               const sf::Vector2f& position, 
                               const T& text, 
                               const std::string& prefix,
                               const std::string& postfix
                               )
{
    std::stringstream str_text;
    str_text << prefix << text << postfix;

    try
    {
        tags.push_back(std::make_shared<TextTag>(*presetTags.at(presetTagId).get()));
        tags.back()->setPosition(position);
        tags.back()->setText(str_text.str());
    }
    catch (std::out_of_range&)
    {
        std::cout << "ERROR in TextTagSystem::addTextTag: there is no preset tag with id = " << presetTagId << '\n';
    }
}


#endif // TEXTTAGSYSTEM_H 
