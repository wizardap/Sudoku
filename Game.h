#ifndef GAME_H
#define GAME_H


#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include "DynamicText.h"
#include "SudokuBoard.h"
class Game
{
public:
    Game();
    virtual ~Game();
    bool init();
    void run();
    void render();
    void close();
private:
    const int SCREEN_HEIGHT=720;
    const int SCREEN_WIDTH = 1100;
    SDL_Window* Game_Window;
    SDL_Renderer* Game_Renderer;
    SudokuBoard board;

};

#endif // GAME_H
