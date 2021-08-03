#ifndef DEFAULTEDITORMODE_H
#define DEFAULTEDITORMODE_H

#include "EditorMode.h"
#include "TextureSelector.h"
#include "Button.h"
#include "Tilemap.h"


class DefaultEditorMode: public EditorMode
{
public:

                                         DefaultEditorMode(sf::Font& font, 
                                                           Tilemap& tilemap,
                                                           sf::RenderWindow& window,
                                                           sf::Vector2i& mousePosWindow,
                                                           sf::Vector2f& mousePosView,
                                                           sf::Vector2i& mousePosGrid,
                                                           std::unordered_map<std::string, sf::Keyboard::Key>& keybinds,
                                                           sf::View& view
                                                           );
                                         ~DefaultEditorMode();
    virtual void                         processEvent(const sf::Event& event);
    virtual void                         update(const float deltaTime);
    virtual void                         render(sf::RenderTarget& target);

private:

    sf::Font&                                           font;
    std::unordered_map<std::string, Button*>            buttons;
    sf::View&                                           view;
                                                        
    sf::RenderWindow&                                   window;
    sf::Vector2i&                                       mousePosWindow;
    sf::Vector2f&                                       mousePosView;
    sf::Vector2i&                                       mousePosGrid;
    std::unordered_map<std::string, sf::Keyboard::Key>& keybinds;

    // Tilemap
    Tilemap&                                            tilemap;
    sf::RectangleShape                                  tileSelector;
    TextureSelector*                                    pTextureSelector;
    bool                                                hideTextureSelector;
    sf::IntRect                                         textureRect;

    // Side bar
    sf::RectangleShape                                  sideBar;
    bool                                                sideBarIsActive;
                                                        
    // Cursor text                                      
    sf::Text                                            cursorText;
    bool                                                tileCanCollide;
    int                                                 tileType;
    int                                                 enemyType;
    int                                                 enemyAmount;
    int                                                 enemyTimeToSpawn;
    float                                               enemyMaxDistance;

                                                        
    // Private functions                                
    void                                 processTilemapEvent(const sf::Event& event);
    void                                 processButtonsEvent(const sf::Event& event);
    void                                 processTextureSelectorEvent(const sf::Event& event);
    void                                 processKeyboardInputEvent(const sf::Event& event);
                                         
    void                                 updateSideBarActivity();
    void                                 updateView(const float deltaTime);
    void                                 updateCursorText();
      
    void                                 renderTilemap(sf::RenderTarget& target);
    void                                 renderTileSelectorAndCursorText(sf::RenderTarget& target);
    void                                 renderTextureSelector(sf::RenderTarget& target);
    void                                 renderButtons(sf::RenderTarget& target);
                                         
    void                                 initSideBar();
    void                                 initButtons();
    void                                 initTextureRect();
    void                                 initTileAndTextureSelectors();
    void                                 initCursorText();

};


#endif // DEFAULTEDITORMODE_H
