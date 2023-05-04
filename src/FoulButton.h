#ifndef FOULBUTTON_H
#define FOULBUTTON_H

#include "Button.h"
#include "Texture.h"
#include <vector>
#include <SDL2/SDL.h>
class FoulButton : public Button
{
public:
    FoulButton();
    virtual ~FoulButton();
    bool init(SDL_Renderer *Foul_Renderer);
    void setDefaultFoul(int value);
    void increaseFoul(int value);
    void draw(SDL_Renderer *Foul_Renderer);
    bool lose();
    void destroy();

private:
    enum FoulState
    {
        FULL,
        EMPTY,
        STATE_TOTAL
    };
    Texture icon[STATE_TOTAL];
    Texture rectangle;
    int defaultFouls;
    int iteratorFouls;
    SDL_Rect center_rect;
};

#endif // FOULBUTTON_H
