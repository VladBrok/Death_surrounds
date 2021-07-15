#include "State.h"


State::State(sf::RenderWindow* pWindow, 
             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
             std::stack<State*>* const pStates
            )
    : pWindow(pWindow), pSupportedKeys(pSupportedKeys), pStates(pStates), stateIsActive(true)
{
}


const bool State::isActive() const 
{
    return stateIsActive;
}


void State::updateActivityStatus()
{
    if (sf::Keyboard::isKeyPressed(keybinds.at("CLOSE_STATE")))
    {
        stateIsActive = false;
    }
}


void State::updateMousePosition()
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(*pWindow);
    mousePosView = pWindow->mapPixelToCoords(mousePosWindow);
}


void State::initKeybinds(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (file.is_open()) // Loading the keys for this state
    {
        std::string action;
        std::string key;
        try
        {
            while (file >> action >> key)
            {
                keybinds[action] = pSupportedKeys->at(key);
            }
        }
        catch (std::out_of_range&)
        {
            std::cout << "ERROR in State::initKeybinds: "
                          "the required keys could not be found among the supported ones\n";
        }
    }
    else
    {
        std::cout << "ERROR in State::initKeybinds: unable to open the file " + filePath << '\n';
    }
}
