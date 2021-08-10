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


void TextTagSystem::initPresetTags()
{
    presetTags[EXPERIENCE_TAG] = 
        std::make_shared<TextTag>(
            TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Cyan, 25, 50.f, 145.f, 1.5f, 4)
        );
    presetTags[DAMAGE_TAG] =
        std::make_shared<TextTag>(
            TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Red, 20, 35.f, 110.f, 1.5f, 0)
        );
    presetTags[LEVEL_UP_TAG] =
        std::make_shared<TextTag>(
            TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Magenta, 30, 160.f, 120.f, 1.4f, 2)
        );
}
