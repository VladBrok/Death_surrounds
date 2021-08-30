#ifndef DEFAULTEDITORMODE_H
#define DEFAULTEDITORMODE_H

#include "typedefs.h"
#include "EditorMode.h"
class TextureSelector;
class Tilemap;


class DefaultEditorMode: public EditorMode
{
public:

                                     DefaultEditorMode(const sf::Font& font, 
                                                       Tilemap& tilemap,
                                                       sf::RenderWindow& window,
                                                       sf::Vector2i& mousePosWindow,
                                                       sf::Vector2f& mousePosView,
                                                       sf::Vector2i& mousePosGrid,
                                                       StringToKeyMap& keybinds,
                                                       sf::View& view
                                                       );
    virtual void                     processEvent(const sf::Event& event);
    virtual void                     update(const float deltaTime);
    virtual void                     render(sf::RenderTarget& target);
                                     
private:                             
                                     
    const sf::Font&                  font;
    StringToButtonMap                buttons;
    sf::View&                        view;
                                     
    sf::RenderWindow&                window;
    sf::Vector2i&                    mousePosWindow;
    sf::Vector2f&                    mousePosView;
    sf::Vector2i&                    mousePosGrid;
    StringToKeyMap&                  keybinds;
                                     
    // Tilemap                       
    Tilemap&                         tilemap;
    sf::RectangleShape               tileSelector;
    std::unique_ptr<TextureSelector> textureSelector;
    bool                             hideTextureSelector;
    sf::IntRect                      textureRect;
                                     
    // Side bar                      
    sf::RectangleShape               sideBar;
    bool                             sideBarIsActive;
                                     
    // Cursor text                   
    sf::Text                         cursorText;
    bool                             tileCanCollide;
    int                              tileType;
    int                              enemyType;
    int                              enemyTimeToSpawn;

                                                        
    // Private functions                                
    void                             processTilemapEvent(const sf::Event& event);
    void                             processButtonsEvent(const sf::Event& event);
    void                             processTextureSelectorEvent(const sf::Event& event);
    void                             processKeyboardInputEvent(const sf::Event& event);
                                     
    void                             updateSideBarActivity();
    void                             updateView(const float deltaTime);
    void                             updateCursorText();
                                     
    void                             renderTilemap(sf::RenderTarget& target);
    void                             renderTileSelectorAndCursorText(sf::RenderTarget& target);
    void                             renderGui(sf::RenderTarget& target);
                                     
    void                             initSideBar();
    void                             initGui();
    void                             initTextureRect();
    void                             initTileSelector();
    void                             initCursorText();
};


#endif // DEFAULTEDITORMODE_H
