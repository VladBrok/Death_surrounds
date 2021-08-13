#include "precompiled.h"
#include "TextTagSystem.h"


TextTagSystem::TextTagSystem(const sf::Font& font)
    : font(font)
{
    initPresetTags();
}


void TextTagSystem::update(const float deltaTime)
{
    auto tag = tags.begin();

    while (tag != tags.end())
    {
        (*tag)->update(deltaTime);

        if ((*tag)->isExpired())
        {
            tag = tags.erase(tag);
        }
        else
        {
            ++tag;
        }
    } 

}


void TextTagSystem::render(sf::RenderTarget& target)
{
    for (auto tag = tags.begin(); tag != tags.end(); ++tag)
    {
        (*tag)->render(target);
    } 
}


const sf::Vector2f& TextTagSystem::getBackElementSize() const
{
    if (tags.empty())
    {
        throw std::runtime_error("ERROR in TextTagSystem::getBackElement: the list of tags is empty\n");
    }
    return tags.back().get()->getSize();
}


void TextTagSystem::setBackElementPosition(const float x, const float y)
{
    if (tags.empty())
    {
        throw std::runtime_error("ERROR in TextTagSystem::setBackElementPosition: the list of tags is empty\n");
    }
    tags.back().get()->setPosition(sf::Vector2f(x, y));
}


void TextTagSystem::initPresetTags()
{
    presetTags.resize(NUMBER_OF_PRESET_TAGS);


    presetTags[EXPERIENCE_TAG] = 
        std::make_shared<TextTag>(
            TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Cyan, 25, 65.f, 105.f, 2.4f, 3)
        );
    presetTags[DAMAGE_TAG] =
        std::make_shared<TextTag>(
            TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Red, 20, 35.f, 110.f, 1.7f, 0)
        );
    presetTags[HEALING_TAG] =
        std::make_shared<TextTag>(
            TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Green, 20, 35.f, 110.f, 1.7f, 0)
        );
    presetTags[LEVEL_UP_TAG] =
        std::make_shared<TextTag>(
            TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Magenta, 30, 160.f, 120.f, 1.5f, 2)
        );
    presetTags[ITEM_NAME_TAG] = 
        std::make_shared<TextTag>(
            TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::White, 20, 140.f, 90.f, 5.f, 2, true)
        );
}
