#ifndef STATE_H
#define STATE_H


class State: public sf::NonCopyable
{
public:
                        State(sf::RenderWindow& window, 
                              const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                              std::stack<State*>* const pStates
                              );
    virtual             ~State();
    virtual void        processEvents(const sf::Event& event);
    virtual void        update(const float deltaTime) = 0;
    virtual void        render(sf::RenderTarget* pTarget = nullptr) = 0; // If pTarget is nullptr, then we render the entity to the window
 
    bool                isActive() const;
    bool                isEventHandler() const; // Returns true if the state needs to process events
    void                endActivity();
    void                pauseState();
    void                unpauseState();
    void                updateMousePosition();

protected:

    sf::RenderWindow&                                                window;
    const std::unordered_map<std::string, sf::Keyboard::Key>* const  pSupportedKeys;
    std::unordered_map<std::string, sf::Keyboard::Key>               keybinds;
    std::stack<State*>* const                                        pStates;
    bool                                                             stateIsActive;
    bool                                                             stateIsPaused;
    bool                                                             stateIsEventHandler;
    std::unordered_map<std::string, sf::Texture>                     textures;
                                                                     
    sf::Vector2i                                                     mousePosScreen;
    sf::Vector2i                                                     mousePosWindow;
    sf::Vector2f                                                     mousePosView;
    sf::Vector2i                                                     mousePosGrid;
                                                                     
    virtual void                                                     initTextures() = 0;
    virtual void                                                     initKeybinds(const std::string& filePath);
};


#endif // STATE_H
