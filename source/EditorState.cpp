#include "precompiled.h"
#include "EditorState.h"
#include "constants.h"


EditorState::EditorState(sf::RenderWindow& window,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(window, pSupportedKeys, pStates), 
      tileMap(10, 7, 1),
      sideBarIsActive(false),
      hideTextureSelector(false)
{
    stateType = STATE_PROCESSES_EVENTS;

    initKeybinds("Config//editorstate_keybinds.ini");
    initFont();
    initSideBar();
    initButtons();
    initPauseMenu();
    initTextureRect();
    initTileAndTextureSelectors();
}


EditorState::~EditorState()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    }    

    delete pPauseMenu;

    delete pTextureSelector;
}


void EditorState::processEvent(const sf::Event& event)
{
    updateMousePosition();


    if (stateIsPaused)
    {
        processPauseMenuEvent(event);
    }
    else
    {
        processButtonsEvent(event);
        updateSideBarActivity();
        tileSelector.setPosition(mousePosGrid.x * GRID_SIZE, mousePosGrid.y * GRID_SIZE);

        // Update the tile map and the texture selector
        if (!sideBarIsActive) 
        {
            processTextureSelectorEvent(event);
            processTileMapEvent(event);  
        }
    }

    /* Pausing or unpausing the state */
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == keybinds.at("PAUSE"))
    {
        stateIsPaused ? unpauseState(): pauseState();
    }
}


void EditorState::processPauseMenuEvent(const sf::Event& event)
{
    pPauseMenu->processEvent(event, mousePosView);


    if (pPauseMenu->isButtonPressed("LOAD"))
    {
        tileMap.loadFromFile("Resources\\Data\\tile_map.txt");
    }

    else if (pPauseMenu->isButtonPressed("SAVE"))
    {
        tileMap.saveToFile("Resources\\Data\\tile_map.txt");
    }

    else if (pPauseMenu->isButtonPressed("GO_TO_MAIN_MENU"))
    {
        endActivity();
    }
}


void EditorState::processButtonsEvent(const sf::Event& event)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->processEvent(event, mousePosView);
    }

    // Open or close the texture selector
    if (buttons["TEXTURE_SELECTOR"]->isPressed(false) ||
       (event.type == sf::Event::KeyPressed &&
        event.key.code ==  keybinds.at("TEXTURE_SELECTOR")))
    {
        hideTextureSelector = !hideTextureSelector;
        if (hideTextureSelector)
        {
            pTextureSelector->endActivity();
        }
    }
}


void EditorState::processTileMapEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && !pTextureSelector->isActive())
    {
        /* Adding the tile */
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            tileMap.addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect);
        }

        /* Removing the tile */
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
            tileMap.removeTile(mousePosGrid.x, mousePosGrid.y, 0);
        }
    } 
}
   

void EditorState::processTextureSelectorEvent(const sf::Event& event)
{
    if (!hideTextureSelector)
    {
        pTextureSelector->processEvent(event, mousePosWindow);
        textureRect = pTextureSelector->getTextureRect();

        tileSelector.setTextureRect(textureRect);
    }
}


void EditorState::updateSideBarActivity()
{
    sideBarIsActive = sideBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow));
}


void EditorState::renderPauseMenu(sf::RenderTarget& target)
{
    if (stateIsPaused)
    {
        pPauseMenu->render(target);
    }
}


void EditorState::renderTileSelector(sf::RenderTarget& target)
{
    if (!pTextureSelector->isActive() && !sideBarIsActive)
    {
        target.draw(tileSelector);
    }
}


void EditorState::renderTextureSelector(sf::RenderTarget& target)
{
    if (!hideTextureSelector)
    {
        pTextureSelector->render(target);
    }
}


void EditorState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }


    tileMap.render(*pTarget);

    pTarget->draw(sideBar);

    renderTileSelector(*pTarget);
    renderTextureSelector(*pTarget);
    renderButtons(*pTarget);
    renderPauseMenu(*pTarget);
}


void EditorState::renderButtons(sf::RenderTarget& target)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(target);
    }
}


void EditorState::initTextures()
{
}


void EditorState::initFont()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
}


void EditorState::initSideBar()
{
    sideBar.setSize(sf::Vector2f(GRID_SIZE, (float)window.getSize().y));
    sideBar.setFillColor(sf::Color(90, 90, 90, 70));
    sideBar.setOutlineColor(sf::Color(140, 140, 140, 140));
    sideBar.setOutlineThickness(1.f);
}


void EditorState::initButtons()
{
    buttons["TEXTURE_SELECTOR"] = new Button(
                                        0.f, 
                                        0.f,
                                        sideBar.getSize().x,
                                        GRID_SIZE / 2.f,
                                        font,
                                        "TS",
                                        sf::Color::White,
                                        sf::Color::White,
                                        sf::Color::White,
                                        sf::Color(130, 130, 130, 100),
                                        sf::Color(160, 160, 160, 170),
                                        sf::Color(190, 190, 190, 190),
                                        sf::Color(200, 200, 200, 220),
                                        sf::Color(220, 220, 220, 240),
                                        sf::Color(240, 240, 240, 240)
                                     );
}


void EditorState::initPauseMenu()
{
    pPauseMenu = new PauseMenu(window, font);

    pPauseMenu->addButton("LOAD", "Load", 2);

    pPauseMenu->addButton("SAVE", "Save", 3);

    pPauseMenu->addButton("GO_TO_MAIN_MENU", "Go to main menu", 5);
}


void EditorState::initTextureRect()
{
    textureRect.width  = static_cast<int>(GRID_SIZE);
    textureRect.height = static_cast<int>(GRID_SIZE);
}


void EditorState::initTileAndTextureSelectors()
{
    tileSelector.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    tileSelector.setFillColor(sf::Color(255, 255, 255, 140));

    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::White);

    tileSelector.setTexture(&tileMap.getTextureSheet());
    tileSelector.setTextureRect(textureRect);

    pTextureSelector = new TextureSelector(
                               GRID_SIZE / 2.f, 
                               GRID_SIZE / 2.f, 
                               GRID_SIZE * 10, 
                               GRID_SIZE * 2, 
                               tileMap.getTextureSheet()
                           );
}
