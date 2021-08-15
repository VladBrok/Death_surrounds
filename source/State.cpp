#include "precompiled.h"
#include "State.h"
#include "constants.h"
#include "Resources.h"


State::State(sf::RenderWindow& window, 
             const StringToKeyMap& supportedKeys,
             std::stack<State*>& states
            )
    : window(window), 
      supportedKeys(supportedKeys), 
      states(states), 
      stateIsActive(true),
      stateIsPaused(false),
      stateType(STATE_DEFAULT)
{
    initFont();
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

    mousePosView = window.mapPixelToCoords(mousePosWindow);
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


void State::initFont()
{
    if (!font.loadFromFile(resources::getFontFile()))
    {
        throw std::runtime_error("ERROR in State::initFont: could not load the font from file " + resources::getFontFile());
    }
}


void State::initKeybinds(const std::string& filePath)
{
    std::ifstream file(filePath);

    // Loading the keys for the state
    if (file.is_open()) 
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
