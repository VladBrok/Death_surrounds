#ifndef STATE_H
#define STATE_H

#include "SFML/Graphics.hpp"
#include <iostream> // Just for debug purposes
#include <unordered_map>
#include <fstream>
#include <stack>


class State: public sf::NonCopyable
{
public:

                        State(sf::RenderWindow* pWindow, 
                              const std::unordered_map<std::string, 
                              sf::Keyboard::Key>* const pSupportedKeys,
                              std::stack<State*>* const pStates
                              );
    virtual             ~State();
    virtual void        update(const float deltaTime) = 0;
    virtual void        updateKeyboardInput(const float deltaTime) = 0;
    virtual void        render(sf::RenderTarget* pTarget = nullptr) = 0;
 
    const bool          isActive() const;
    void                endActivity();
    void                updateMousePosition();

protected:

    sf::RenderWindow*                                                   pWindow;
    const std::unordered_map<std::string, sf::Keyboard::Key>* const     pSupportedKeys;
    std::unordered_map<std::string, sf::Keyboard::Key>                  keybinds;
    std::stack<State*>* const                                           pStates;
    bool                                                                stateIsActive;
    std::unordered_map<std::string, sf::Texture>                        textures;

    sf::Vector2i        mousePosScreen;
    sf::Vector2i        mousePosWindow;
    sf::Vector2f        mousePosView;

    virtual void        initTextures() = 0;
    virtual void        initKeybinds(const std::string& filePath);

};


#endif // STATE_H
