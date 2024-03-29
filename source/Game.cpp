#include "precompiled.h"
#include "Game.h"
#include "constants.h"
#include "Resources.h"


Game::Game()
    : windowHasFocus(true)
{
    initWindow();
    initSupportedKeys();
    initStates();
}


void Game::run()
{
    while (window.isOpen())
    {
        updateDeltaTime();
        processEvents();
        update();
        render();
    }
}



void Game::updateDeltaTime()
{
    deltaTime = clock.restart().asSeconds();
}


void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        /* 
           Closing the window if the red button with 
           white cross is pressed
        */
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        
        // Updating the focus of the window
        else if (event.type == sf::Event::LostFocus)
        {
            windowHasFocus = false;
        }
        else if (event.type == sf::Event::GainedFocus)
        {
            windowHasFocus = true;
        }

        
        if (!states.empty() && windowHasFocus)
        {
            states.top()->processEvent(event);
        }
    }
}


void Game::update()
{
    if (!states.empty()) // Updating states
    {
        if (!windowHasFocus)
        {
            return;
        }

        states.top()->update(deltaTime);

        if (!states.top()->isActive())
        {
            states.pop();
        }
    }
    else // Closing the window if there are no states left
    {
        window.close();
    }
}


void Game::render()
{
    window.clear();

    if (!states.empty())
    {
        states.top()->render();
    }

    window.display();
}


void Game::initWindow()
{
    const std::vector<sf::VideoMode>& videoModes = sf::VideoMode::getFullscreenModes();

    window.create(videoModes[0],
                  "Death surrounds",
                  sf::Style::Close
                  );

    window.setFramerateLimit(FPS_LIMIT);
}


void Game::initSupportedKeys()
{
    std::string path = resources::getSupportedKeysFile();
    std::ifstream file(path);

    if (file.is_open()) // Reading the keys and their codes from file
    {
        std::string keyName;
        int keyCode;
        while (file >> keyName >> keyCode)
        {
            supportedKeys[keyName] = static_cast<sf::Keyboard::Key>(keyCode);
        }
        file.close();
    }
    else
    {
        throw std::runtime_error("ERROR in Game::initSupportedKeys: unable to open the file " + path + "\n");
    }
}


void Game::initStates()
{
    std::unique_ptr<State> state(new MainMenuState(window, supportedKeys, states));
    states.push(std::move(state));
}
