#ifndef LEVEL__H_
#define LEVEL__H_

#include <string>
#include <random>
#include <chrono>
#include <cstdlib>
#include "TextButton.h"
#include "Texture.h"
#include <SDL2/SDL.h>
#include <cassert>

class Level
{
public:
    Level();
    ~Level();
    bool init(SDL_Renderer *Level_Renderer);
    int getDifficulty(SDL_Renderer *Level_Renderer);
    void draw(SDL_Renderer *Level_Renderer);
    void destroy();

private:
    enum LevelState
    {
        SUPER_EASY,
        EASY,
        MEDIUM,
        HARD,
        INSANE,
        TOTAL
    };
    const std::string LEVEL_NAME[TOTAL] = {"Super Easy", "Easy", "Medium", "Hard", "Insane"};
    Texture gBackground;
    TextButton gButton[TOTAL];
    int Rand(int l, int r)
    {
        if (l > r)
            return -1;
        std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        return l + rng() % (r - l + 1);
    }
};

#endif // LEVEL__H_