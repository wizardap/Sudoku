#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "DynamicText.h"
#include "SudokuBoard.h"
#include "TimerButton.h"
#include "SDK_ults.h"
#include "FoulButton.h"
#include "NoticeWindow.h"
#include "Options.h"
#include "Menu.h"
#include "Texture.h"
#include "Level.h"

class Game
{
public:
    Game();
    virtual ~Game();
    bool init();
    void run();
    int start();
    void pause();
    void surrender(bool value);
    void render();
    void close();

private:
    const int SCREEN_HEIGHT = 720;
    const int SCREEN_WIDTH = 1080;

    SDL_Window *Game_Window;
    SDL_Renderer *Game_Renderer;
    SudokuBoard Game_Board;
    TimerButton Game_Timer;
    FoulButton Game_Turn;
    Options Game_Option;
    SDL_Surface *WindowLogo;
    Texture Game_Over;
    NoticeWindow Game_Notice;
    Menu Game_Menu;
    Level Game_Level;

    int allow_fouls = 3;
    bool started;
    bool paused;
    bool give_up;
};

#endif // GAME_H
