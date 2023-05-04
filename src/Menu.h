#ifndef MENU_H
#define MENU_H

#include "TextButton.h"
#include "IconButton.h"
#include "Texture.h"
#include "SDK_ults.h"
class Menu
{
public:
    Menu();
    virtual ~Menu();
    bool init(SDL_Renderer *Menu_Renderer);
    void run(SDL_Renderer *Menu_Renderer, SoundManager *SoundPlay);
    bool isNewGame();
    bool isQuit();
    bool isTutorial();
    void destroy();
    void draw(SDL_Renderer *Menu_Renderer);

private:
    enum ButtonType
    {
        NEWGAME,
        TUTORIAL,
        RULE,
        QUIT,
        TYPE_TOTAL
    };

    enum State
    {
        MAIN,
        TUTORIAL_MAIN,
        RULE_MAIN,
        STATE_TOTAL
    };

    State gCurrentState;
    ButtonType gCurrentButtonType;
    TextButton gButtonText[TYPE_TOTAL];
    IconButton gReturn;
    Texture menu_background, tutorial_background, rule_background;
};

#endif // MENU_H
