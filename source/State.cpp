#include "precompiled.h"
#include "State.h"
#include "constants.h"


State::State(sf::RenderWindow& window, 
             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
             std::stack<State*>* const pStates
            )
    : window(window), 
      pSupportedKeys(pSupportedKeys), 
      pStates(pStates), 
      stateIsActive(true),
      stateIsPaused(false),
      stateIsEventHandler(false)
{
}


State::~State()
{
}


void State::processEvents(const sf::Event& event)
{
}


bool State::isActive() const 
{
    return stateIsActive;
}


bool State::isEventHandler() const
{
    return stateIsEventHandler;
}


void State::endActivity()
{
    stateIsActive = false;
}


void State::pauseState()
{
    stateIsPaused = true;
}


void State::unpauseState()
{
    stateIsPaused = false;
}


void State::updateMousePosition()
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(window);
    mousePosView   = window.mapPixelToCoords(mousePosWindow);

    mousePosGrid.x = static_cast<int>(mousePosView.x) / static_cast<int>(GRID_SIZE);
    mousePosGrid.y = static_cast<int>(mousePosView.y) / static_cast<int>(GRID_SIZE);
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

