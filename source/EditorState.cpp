#include "precompiled.h"
#include "EditorState.h"
#include "constants.h"


EditorState::EditorState(sf::RenderWindow& window,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(window, pSupportedKeys, pStates), 
      tileMap(TILEMAP_SIZE_X, TILEMAP_SIZE_Y, TILEMAP_SIZE_Z),
      sideBarIsActive(false),
      hideTextureSelector(false),
      tileCanCollide(false)
{
    stateType = STATE_UPDATES_AND_PROCESSES_EVENTS;

    initKeybinds("Config//editorstate_keybinds.ini");
    initFont();
    initSideBar();
    initButtons();
    initPauseMenu();
    initTextureRect();
    initTileAndTextureSelectors();
    initView();
    initCursorText();
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


/*=============== Event processors ===============*/

void EditorState::processEvent(const sf::Event& event)
{
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
            processTilemapEvent(event);  
        }
    }


    if (event.type == sf::Event::KeyPressed)
    {
        // Pausing or unpausing the state
        if (event.key.code == keybinds.at("PAUSE"))
        {
            stateIsPaused ? unpauseState(): pauseState();
        }

        // Changing the tileCanCollide status
        else if (event.key.code == keybinds.at("TILE_COLLISION"))
        {
            tileCanCollide = !tileCanCollide;
        }
    }
}


void EditorState::processPauseMenuEvent(const sf::Event& event)
{
    pPauseMenu->processEvent(event, mousePosWindow);


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
        b->second->processEvent(event, mousePosWindow);
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


void EditorState::processTilemapEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && !pTextureSelector->isActive())
    {
        // Adding the tile
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            tileMap.addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect, tileCanCollide);
        }

        // Removing the tile
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


/*=============== Update functions ===============*/ 

void EditorState::update(const float deltaTime)
{
    updateMousePosition(&view);
    updateView(deltaTime);

    if (!stateIsPaused)
    {
        updateCursorText();
    }
}


void EditorState::updateSideBarActivity()
{
    sideBarIsActive = sideBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow));
}


void EditorState::updateView(const float deltaTime)
{
    const float viewSpeed = 260.f * deltaTime;

    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_UP")))
    {
        view.move(0.f, -viewSpeed);

        // Adjusting the view vertical position 
        if (view.getCenter().y - view.getSize().y / 2.f < 0.f)
        {
            view.setCenter(view.getCenter().x, view.getSize().y / 2.f);
        }
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_DOWN")))
    {
        view.move(0.f, viewSpeed);
    }
    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_LEFT")))
    {
        view.move(-viewSpeed, 0.f);

        // Adjusting the view horizontal position
        if (view.getCenter().x - view.getSize().x / 2.f < 0.f - sideBar.getSize().x)
        {
            view.setCenter(view.getSize().x / 2.f - sideBar.getSize().x, view.getCenter().y);
        }
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_RIGHT")))
    {
        view.move(viewSpeed, 0.f);
    }
}


void EditorState::updateCursorText()
{
    std::stringstream sstream;
    sstream << "Grid position:     (" << mousePosGrid.x << ';' << mousePosGrid.y << ")\n";
    sstream << "Tile can collide:  " << (tileCanCollide ? "true": "false") << '\n';

    cursorText.setString(sstream.str());
    cursorText.setPosition(mousePosView.x + 15.f, mousePosView.y);
}


/*=============== Render functions ===============*/

void EditorState::renderTileSelectorAndCursorText(sf::RenderTarget& target)
{
    if (!pTextureSelector->isActive() && !sideBarIsActive)
    {
        target.setView(view);
        target.draw(tileSelector);
        target.draw(cursorText);
        target.setView(window.getDefaultView());
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


    pTarget->setView(view);

    tileMap.render(*pTarget);

    pTarget->setView(pTarget->getDefaultView());


    pTarget->draw(sideBar);

    renderTileSelectorAndCursorText(*pTarget);
    renderTextureSelector(*pTarget);
    renderButtons(*pTarget);


    if (stateIsPaused)
    {
        pPauseMenu->render(*pTarget);
    }
}


void EditorState::renderButtons(sf::RenderTarget& target)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(target);
    }
}


/*=============== Initializers ===============*/

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


void EditorState::initView()
{
    view.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
}


void EditorState::initCursorText()
{
    cursorText.setCharacterSize(window.getSize().y / 35);
    cursorText.setFont(font);
}
