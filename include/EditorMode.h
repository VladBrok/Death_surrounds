#ifndef EDITORMODE_H
#define EDITORMODE_H


enum EditorModes
{
    DEFAULT_MODE,
    NUMBER_OF_EDITOR_MODES
};


class EditorMode: public sf::NonCopyable
{
public:

    virtual void processEvent(const sf::Event& event) = 0;
    virtual void update(const float deltaTime) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};


#endif // EDITORMODE_H
