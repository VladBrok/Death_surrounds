
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