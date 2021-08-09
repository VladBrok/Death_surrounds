#include "precompiled.h"
#include "State.h"
#include "constants.h"


State::State(sf::RenderWindow& window, 
             const std::unordered_map<std::string, sf::Keyboard::Key>& supportedKeys,
             std::stack<State*>& states
            )
    : window(window), 
      supportedKeys(supportedKeys), 
      states(states), 
      stateIsActive(true),
      stateIsPaused(false),
      stateType(STATE_DEFAULT)
{
}


bool State::isActive() const 
{
    return stateIsActive;
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


void State::updateMousePosition(sf::View* pView)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(window);

    if (pView)
    {
        window.setView(*pView);
    }

    mousePosView   = window.mapPixelToCoords(mousePosWindow);
    window.setView(window.getDefaultView());

    mousePosGrid.x = static_cast<int>(mousePosView.x) / static_cast<int>(GRID_SIZE);
    mousePosGrid.y = static_cast<int>(mousePosView.y) / static_cast<int>(GRID_SIZE);
}


bool State::needToCallUpdate() const
{
    return stateType == STATE_UPDATES || stateType == STATE_UPDATES_AND_PROCESSES_EVENTS;
}


bool State::needToCallProcessEvent() const
{
    return stateType == STATE_PROCESSES_EVENTS || stateType == STATE_UPDATES_AND_PROCESSES_EVENTS;
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
                keybinds[action] = supportedKeys.at(key);
            }
        }
        catch (std::out_of_range&)
        {
            throw std::runtime_error(
                      "ERROR in State::initKeybinds: "
                      "the required keys could not be found among the supported ones\n"
                       );
        }
    }
    else
    {
        throw std::runtime_error("ERROR in State::initKeybinds: unable to open the file " + filePath + "\n");
    }
}
