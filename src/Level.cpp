#include "Level.h"
Level::Level()
{
    for (int i = 0; i < TOTAL; i++)
        gButton[i].setRect({650, 250 + 50 * i, 0, 0});
}

Level::~Level()
{
    destroy();
}

bool Level::init(SDL_Renderer *Level_Renderer)
{
    for (int i = 0; i < TOTAL; i++)
        if (gButton[i].init(Level_Renderer, LEVEL_NAME[i]) == false)
        {
            SDL_Log("Failed to load %s button in SDK_ults.cpp!", LEVEL_NAME[i].c_str());
            return false;
        }
    if (gBackground.loadImage(Level_Renderer, "assets/Background/background.png") == false)
    {
        SDL_Log("Failed to load background image in SDK_ults.cpp");
        return false;
    }
    return true;
}

int Level::getDifficulty(SDL_Renderer *Level_Renderer)
{
    SDL_Event e;
    bool running = true;
    int diff = -1;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
                diff = -1;
                break;
            }

            for (int i = 0; i < TOTAL; i++)
            {
                gButton[i].update(e);
                if (gButton[i].isSelected())
                    running = false;
            }
            if (gButton[SUPER_EASY].isSelected())
            {
                diff = 5;
            }
            if (gButton[EASY].isSelected())
            {
                diff = Rand(20, 25);
            }
            if (gButton[MEDIUM].isSelected())
            {
                diff = Rand(31, 38);
            }
            if (gButton[HARD].isSelected())
            {
                diff = Rand(39, 42);
                assert(diff >= 39 && diff <= 42);
            }
            if (gButton[INSANE].isSelected())
            {
                diff = 52;
            }
        }
        draw(Level_Renderer);
    }
    return diff;
}

void Level::draw(SDL_Renderer *Level_Renderer)
{
    SDL_RenderClear(Level_Renderer);
    gBackground.render(Level_Renderer, 0, 0);
    for (int i = 0; i < TOTAL; i++)
        gButton[i].draw(Level_Renderer);
    SDL_RenderPresent(Level_Renderer);
}

void Level::destroy()
{
    gBackground.destroy();
    for (int i = 0; i < TOTAL; i++)
        gButton[i].destroy();
}