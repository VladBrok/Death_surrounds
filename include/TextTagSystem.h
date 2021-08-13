#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H


enum PresetTextTagId
{
    EXPERIENCE_TAG,
    DAMAGE_TAG,
    HEALING_TAG,
    LEVEL_UP_TAG,
    ITEM_NAME_TAG,
    NUMBER_OF_PRESET_TAGS
};


class TextTagSystem: public sf::NonCopyable
{
public:

                           TextTagSystem(const sf::Font& font);
                           
    void                   update(const float deltaTime);
    void                   render(sf::RenderTarget& target);
    const sf::Vector2f&    getBackElementSize() const;
    void                   setBackElementPosition(const float x, const float y);

    template <class T>
    void                   addTextTag(const int presetTagId, 
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
        float       deceleration;
        int         fadeValue;
        bool        renderToWindow;


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
                const float deceleration = 0,
                const int fadeValue = 0,
                const bool renderToWindow = false
                )
                : movementDirX(movementDirX),
                  movementDirY(movementDirY),
                  lifetime(lifetime),
                  speed(speed),
                  deceleration(deceleration),
                  fadeValue(fadeValue),
                  renderToWindow(renderToWindow)
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

                // Moving the text
                sfmlText.setPosition(
                    (float)(int)(sfmlText.getPosition().x + movementDirX * speed * deltaTime),
                    (float)(int)(sfmlText.getPosition().y + movementDirY * speed * deltaTime)
                 );

                if (speed >= deceleration)
                {
                    speed -= deceleration;
                }

                if (fadeValue > 0 && sfmlText.getColor().a >= fadeValue)
                {
                    sfmlText.setColor(
                        sf::Color(
                            sfmlText.getColor().r,
                            sfmlText.getColor().g,
                            sfmlText.getColor().b,
                            sfmlText.getColor().a - (sf::Uint8)fadeValue
                        )
                    );
                }
            }
        }

        void render(sf::RenderTarget& target)
        {
            if (renderToWindow)
            {
                const sf::View view = target.getView();
                target.setView(target.getDefaultView());
                target.draw(sfmlText);
                target.setView(view);
            }
            else
            {
                target.draw(sfmlText);
            }
        }

        bool isExpired() const
        {
            return lifetime <= 0.f;
        }

        const sf::Vector2f getSize() const
        {
            return sf::Vector2f(sfmlText.getGlobalBounds().width, sfmlText.getGlobalBounds().height);
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

    typedef std::list<std::shared_ptr<TextTag>> TagsContainer;
    typedef std::vector<std::shared_ptr<TextTag>> PresetTagsContainer;


    const sf::Font&        font;
    TagsContainer          tags;
    PresetTagsContainer    presetTags;

    void                   initPresetTags();
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
