#ifndef STATE_H
#define STATE_H


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
                              const std::unordered_map<std::string, sf::Keyboard::Key>& supportedKeys,
                              std::stack<State*>& states
                              );
    virtual             ~State() {};
    virtual void        processEvent(const sf::Event& event) {};
    virtual void        update(const float deltaTime) {};
    virtual void        render(sf::RenderTarget* pTarget = nullptr) = 0; // If pTarget is nullptr, then we render the entity to the window
 
    bool                isActive() const;
    void                endActivity();
    void                pauseState();
    void                unpauseState();
    void                updateMousePosition(sf::View* pView = nullptr);

    bool                needToCallUpdate() const;
    bool                needToCallProcessEvent() const;

protected:

    sf::RenderWindow&                                          window;
    const std::unordered_map<std::string, sf::Keyboard::Key>&  supportedKeys;
    std::stack<State*>&                                        states;
    std::unordered_map<std::string, sf::Keyboard::Key>         keybinds;
    bool                                                       stateIsActive;
    bool                                                       stateIsPaused;
    StateType                                                  stateType;
    std::unordered_map<std::string, sf::Texture>               textures;
                                                               
    sf::Vector2i                                               mousePosScreen;
    sf::Vector2i                                               mousePosWindow;
    sf::Vector2f                                               mousePosView;
    sf::Vector2i                                               mousePosGrid;
                                                               
    virtual void                                               initTextures() {};
    virtual void                                               initKeybinds(const std::string& filePath);
};


#endif // STATE_H
