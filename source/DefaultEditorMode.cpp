#include "precompiled.h"
#include "DefaultEditorMode.h"
#include "constants.h"
#include "EnemySystem.h"
#include "TextureSelector.h"
#include "Button.h"
#include "Tilemap.h"


DefaultEditorMode::DefaultEditorMode(const sf::Font& font,
                                     Tilemap& tilemap,
                                     sf::RenderWindow& window,
                                     sf::Vector2i& mousePosWindow,
                                     sf::Vector2f& mousePosView,
                                     sf::Vector2i& mousePosGrid,
                                     StringToKeyMap& keybinds,
                                     sf::View& view
                                     )
  : font(font),
    tilemap(tilemap),
    window(window),
    mousePosWindow(mousePosWindow),
    mousePosView(mousePosView),
    mousePosGrid(mousePosGrid),
    keybinds(keybinds),
    view(view),
    sideBarIsActive(false),
    hideTextureSelector(false),
    tileCanCollide(false),
    tileType(0),
    enemyType(0),
    enemyTimeToSpawn(0)
{
    initSideBar();
    initTextureRect();
    initGui();
    initTileSelector();
    initCursorText();

    view.setCenter(window.getSize().x / 2.f - sideBar.getSize().x, window.getSize().y / 2.f);
}


void DefaultEditorMode::processEvent(const sf::Event& event)
{
    processButtonsEvent(event);

    if (!sideBarIsActive)
    {
        processTilemapEvent(event);
        processTextureSelectorEvent(event);
    }

    processKeyboardInputEvent(event);
}


void DefaultEditorMode::update(const float deltaTime)
{
    updateSideBarActivity();
    updateView(deltaTime);
    updateCursorText();

    tileSelector.setPosition(mousePosGrid.x * GRID_SIZE, mousePosGrid.y * GRID_SIZE);
}


void DefaultEditorMode::render(sf::RenderTarget& target)
{
    renderTilemap(target);

    target.draw(sideBar);

    renderTileSelectorAndCursorText(target);
    renderGui(target);
}



void DefaultEditorMode::processTilemapEvent(const sf::Event& event)
{
    // Adding the tile
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !textureSelector->isActive())
    {
        if (tileType == ENEMY_SPAWNER)
        {
            tilemap.addEnemySpawnerTile(mousePosGrid.x, 
                                        mousePosGrid.y, 
                                        textureRect, 
                                        tileCanCollide,
                                        enemyType, 
                                        enemyTimeToSpawn
                                        );
        }
        else
        {
            tilemap.addTile(mousePosGrid.x, 
                            mousePosGrid.y, 
                            textureRect, 
                            tileCanCollide, 
                            static_cast<TileType>(tileType)
                            );
        }
    }

    // Removing the tile
    else if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Right &&
             !textureSelector->isActive()
             )
    {
        tilemap.removeTile(mousePosGrid.x, mousePosGrid.y);
    } 
}


void DefaultEditorMode::processButtonsEvent(const sf::Event& event)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->processEvent(event, mousePosWindow);
    }

    // Open or close the texture selector
    if (buttons["TEXTURE_SELECTOR"]->isPressed(false) ||
       (event.type == sf::Event::KeyPressed &&
        event.key.code == keybinds.at("TEXTURE_SELECTOR")))
    {
        hideTextureSelector = !hideTextureSelector;
        if (hideTextureSelector)
        {
            textureSelector->endActivity();
        }
    }
}


void DefaultEditorMode::processTextureSelectorEvent(const sf::Event& event)
{
    if (!hideTextureSelector)
    {
        textureSelector->processEvent(event, mousePosWindow);
        textureRect = textureSelector->getTextureRect();

        tileSelector.setTextureRect(textureRect);
    }
}


void DefaultEditorMode::processKeyboardInputEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Changing the tileCanCollide status
        if (event.key.code == keybinds.at("TILE_COLLISION"))
        {
            tileCanCollide = !tileCanCollide;
        }

        // Changing the tile type
        else if (event.key.code == keybinds.at("TILE_TYPE"))
        {
            tileType = (tileType + 1 >= NUMBER_OF_TILE_TYPES) ? 0: (tileType + 1);
        }


        if (tileType == ENEMY_SPAWNER)
        {
            if (event.key.code == keybinds.at("ENEMY_TYPE_UP"))
            {
                if (sf::Keyboard::isKeyPressed(keybinds.at("DECREASE_VALUE")))
                {
                    enemyType = (enemyType - 1 < 0) ? 0: (enemyType - 1);
                }
                else
                {
                    enemyType = (enemyType + 1 >= NUMBER_OF_ENEMY_TYPES) ? (NUMBER_OF_ENEMY_TYPES - 1): (enemyType + 1);
                }
            }
            else if (event.key.code == keybinds.at("ENEMY_TIME_TO_SPAWN_UP"))
            {
                if (sf::Keyboard::isKeyPressed(keybinds.at("DECREASE_VALUE")))
                {
                    enemyTimeToSpawn = (enemyTimeToSpawn - 1 < 0) ? 0: (enemyTimeToSpawn - 1); 
                }
                else
                {
                    ++enemyTimeToSpawn;
                } 
            }
        }
    }
}


void DefaultEditorMode::updateSideBarActivity()
{
    sideBarIsActive = sideBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow));
}


void DefaultEditorMode::updateView(const float deltaTime)
{
    const float VIEW_SPEED = 500.f * deltaTime;

    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_UP")))
    {
        view.move(0.f, -VIEW_SPEED);

        // Adjusting the view vertical position 
        if (view.getCenter().y - view.getSize().y / 2.f < 0.f)
        {
            view.setCenter(view.getCenter().x, view.getSize().y / 2.f);
        }
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_DOWN")))
    {
        view.move(0.f, VIEW_SPEED);
    }
    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_LEFT")))
    {
        view.move(-VIEW_SPEED, 0.f);

        // Adjusting the view horizontal position
        if (view.getCenter().x - view.getSize().x / 2.f < 0.f - sideBar.getSize().x)
        {
            view.setCenter(view.getSize().x / 2.f - sideBar.getSize().x, view.getCenter().y);
        }
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_VIEW_RIGHT")))
    {
        view.move(VIEW_SPEED, 0.f);
    }


    view.setCenter(
        sf::Vector2f(
            std::floor(view.getCenter().x), 
            std::floor(view.getCenter().y)
        )
    );
}


void DefaultEditorMode::updateCursorText()
{
    std::stringstream sstream;
    sstream << "Grid position: (" << mousePosGrid.x << ';' << mousePosGrid.y << ")\n"
            << "Tile can collide: " << (tileCanCollide ? "true": "false") << '\n'
            << "Tile type: " << tilemap.getTileTypeAsString(static_cast<TileType>(tileType)) << '\n';

    if (tileType == ENEMY_SPAWNER)
    {
        sstream << "     Enemy type: " << EnemySystem::getEnemyTypeAsString(enemyType) << '\n'
                << "     Spawn frequency: " << enemyTimeToSpawn << " s" << '\n';
    } 

    sstream << "Number of tiles: " << tilemap.getNumberOfTilesAtPosition(mousePosGrid) << '\n';

    cursorText.setString(sstream.str());
    cursorText.setPosition(mousePosView.x + 15.f, mousePosView.y);
}


void DefaultEditorMode::renderTilemap(sf::RenderTarget& target)
{
    target.setView(view);

    tilemap.render(target, view, mousePosGrid, nullptr, sf::Vector2f(), true, true);

    tilemap.renderDeferred(target);

    target.setView(target.getDefaultView());
}


void DefaultEditorMode::renderTileSelectorAndCursorText(sf::RenderTarget& target)
{
    if (!textureSelector->isActive() && !sideBarIsActive)
    {
        target.setView(view);
        target.draw(tileSelector);
        target.draw(cursorText);
        target.setView(window.getDefaultView());
    }
}


void DefaultEditorMode::renderGui(sf::RenderTarget& target)
{
    // Texture selector
    if (!hideTextureSelector)
    {
        textureSelector->render(target);
    }

    // Buttons
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(target);
    }
}


void DefaultEditorMode::initSideBar()
{
    sideBar.setSize(sf::Vector2f(GRID_SIZE * 1.7f, (float)window.getSize().y));
    sideBar.setFillColor(sf::Color(90, 90, 90, 70));
    sideBar.setOutlineColor(sf::Color(140, 140, 140, 140));
    sideBar.setOutlineThickness(1.f);
}


void DefaultEditorMode::initGui()
{
    /*=============== Buttons ===============*/

    buttons["TEXTURE_SELECTOR"].reset(
        new Button(
               0.f, 
               0.f,
               sideBar.getSize().x,
               GRID_SIZE / 1.2f,
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
        )
    );


    /*=============== Texture selector ===============*/

    textureSelector.reset(
        new TextureSelector(
              sideBar.getSize().x + 2.5f, 
              GRID_SIZE / 2.f, 
              (float)tilemap.getTextureSheet().getSize().x, 
              (float)tilemap.getTextureSheet().getSize().y, 
              tilemap.getTextureSheet()
        )
    );
}


void DefaultEditorMode::initTextureRect()
{
    textureRect.width  = static_cast<int>(GRID_SIZE);
    textureRect.height = static_cast<int>(GRID_SIZE);
}


void DefaultEditorMode::initTileSelector()
{
    tileSelector.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    tileSelector.setFillColor(sf::Color(255, 255, 255, 140));

    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::White);

    tileSelector.setTexture(&tilemap.getTextureSheet());
    tileSelector.setTextureRect(textureRect);
}


void DefaultEditorMode::initCursorText()
{
    cursorText.setCharacterSize(window.getSize().y / 35);
    cursorText.setFont(font);
}
