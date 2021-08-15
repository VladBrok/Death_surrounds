#ifndef STATE_H
#define STATE_H

#include "typedefs.h"


enum StateType
{
    STATE_DEFAULT, // Type of base class State
    STATE_UPDATES, // Has redefined "update" method
    STATE_PROCESSES_EVENTS, // Has redefined "processEvent" method
    STATE_UPDATES_AND_PROCESSES_EVENTS // Has both "update" and "processEvent" methods
};


class State: public sf::NonCopyable
{
public:
                             State(sf::RenderWindow& window, 
                                   const StringToKeyMap& supportedKeys,
                                   std::stack<State*>& states
                                   );
    virtual                  ~State() {};
    virtual void             processEvent(const sf::Event& event) {};
    virtual void             update(const float deltaTime) {};

    // If pTarget is nullptr, then everything renders to the window
    virtual void             render(sf::RenderTarget* pTarget = nullptr) = 0; 
                             
    bool                     isActive() const;
    void                     endActivity();
    void                     pauseState();
    void                     unpauseState();
                             
    bool                     needToCallUpdate() const;
    bool                     needToCallProcessEvent() const;

protected:

    sf::RenderWindow&        window;
    sf::Font                 font;
    const StringToKeyMap&    supportedKeys;
    std::stack<State*>&      states;
    StringToKeyMap           keybinds;
    bool                     stateIsActive;
    bool                     stateIsPaused;
    StateType                stateType;
    StringToTextureMap       textures;
                                                               
    sf::Vector2i             mousePosScreen;
    sf::Vector2i             mousePosWindow;
    sf::Vector2f             mousePosView;
    sf::Vector2i             mousePosGrid;

    void                     updateMousePosition(sf::View* pView = nullptr);
                             
    void                     initFont();
    virtual void             initTextures() {};
    virtual void             initKeybinds(const std::string& filePath);
};


#endif // STATE_H
