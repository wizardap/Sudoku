#include "Game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}
bool Game::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        SDL_Log("SDL could not be intialized! SDL Error: %s\n",SDL_GetError());
        return false;
    }
    Game_Window = SDL_CreateWindow("Sudoku",SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN
                                  );

    if (Game_Window == NULL)
    {
        SDL_Log("Window could not be created! SDL Error: %s\n",SDL_GetError());
        return false;
    }

    Game_Renderer = SDL_CreateRenderer(Game_Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (Game_Renderer == NULL)
    {
        SDL_Log("Renderer could not be created! SDL Error :%s\n",SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(Game_Renderer,255,255,255,255);
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        SDL_Log("Image could not be initialized! IMG Error :%s\n",IMG_GetError());
        return false;
    }

    if (TTF_Init()==-1)
    {
        SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
    return true;
}
void Game::render()
{
    SDL_SetRenderDrawColor(Game_Renderer,255,255,255,255);
    SDL_RenderClear(Game_Renderer);
    board.draw(Game_Renderer);
    SDL_RenderPresent(Game_Renderer);
}

void Game::run()
{
    if (!init())
    {
        SDL_Log("Failed to initialize");
        return;
    }
    SDL_Event e;
    board.setDifficulty(50);
    bool quit =false;
    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) quit = true;
            else
            {
                board.update(e);

            }
        }
        render();
    }

    close();

}

void Game::close()
{
    SDL_DestroyRenderer(Game_Renderer);
    Game_Renderer = NULL;

    SDL_DestroyWindow(Game_Window);
    Game_Window = NULL;
}
