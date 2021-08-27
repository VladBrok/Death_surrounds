#ifndef STATE_H
#define STATE_H

#include "typedefs.h"


class State: public sf::NonCopyable
{
public:
                             State(sf::RenderWindow& window, 
                                   const StringToKeyMap& supportedKeys,
                                   std::stack<State*>& states
                                   );
    virtual                  ~State() {};
    virtual void             processEvent(const sf::Event& event);
    virtual void             update(const float deltaTime);

    // If pTarget is nullptr, then everything renders to the window
    virtual void             render(sf::RenderTarget* pTarget = nullptr) = 0; 
                             
    bool                     isActive() const;
    void                     endActivity();
    void                     pauseState();
    void                     unpauseState();

protected:

    sf::RenderWindow&        window;
    sf::Font                 font;
    const StringToKeyMap&    supportedKeys;
    std::stack<State*>&      states;
    StringToKeyMap           keybinds;
    bool                     stateIsActive;
    bool                     stateIsPaused;
    StringToTextureMap       textures;
                                                               
    sf::Vector2i             mousePosScreen;
    sf::Vector2i             mousePosWindow;
    sf::Vector2f             mousePosView;
    sf::Vector2i             mousePosGrid;

    void                     updateMousePosition(sf::View* pView = nullptr);
                             
    void                     initFont();
    virtual void             initTextures();
    virtual void             initKeybinds(const std::string& filePath);
};


#endif // STATE_H
