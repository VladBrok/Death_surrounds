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


void TextTagSystem::addTextTag(const int presetTagId, const sf::Vector2f& position, const std::string& text)
{
    addTag(presetTagId, position, text);
}


void TextTagSystem::addTextTag(const int presetTagId, const sf::Vector2f& position, const int text)
{
    std::stringstream sstream;
    sstream << text;
    addTag(presetTagId, position, sstream.str());
}


void TextTagSystem::initPresetTags()
{
    presetTags[DEFAULT_TAG] = 
        std::make_shared<TextTag>(
            font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::White, 30, 70.f, 200.f
        );
    presetTags[EXPERIENCE_TAG] = 
        std::make_shared<TextTag>(
            font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Cyan, 30, 70.f, 170.f
        );
    presetTags[DAMAGE_TAG] =
        std::make_shared<TextTag>(
            font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Red, 20, 45.f, 140.f
        );
}


void TextTagSystem::addTag(const int presetTagId, const sf::Vector2f& position, const std::string& text)
{
    try
    {
        tags.push_back(std::make_shared<TextTag>(*presetTags.at(presetTagId).get()));
        tags.back()->setPosition(position);
        tags.back()->setText(text);
    }
    catch (std::out_of_range&)
    {
        std::cout << "ERROR in TextTagSystem::addTextTag: there is no preset tag with id = " << presetTagId << '\n';
    }
}