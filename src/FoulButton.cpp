#include "FoulButton.h"
FoulButton::FoulButton()
{
    gButtonRect = {800, 113, 220, 80};
}

FoulButton::~FoulButton()
{
    destroy();
}
bool FoulButton::init(SDL_Renderer *Foul_Renderer)
{
    if (icon[FULL].loadImage(Foul_Renderer, "assets/Heart/heart_remaining.png") == false)
    {
        SDL_Log("Failed to load FULL icon in FoulButton.h");
        return false;
    }
    if (icon[EMPTY].loadImage(Foul_Renderer, "assets/Heart/heart_dead.png") == false)
    {
        SDL_Log("Failed to load EMPTY icon in FoulButton.h");
        return false;
    }
    if (rectangle.loadImage(Foul_Renderer, "assets/Heart/heart_rect.png") == false)
    {
        SDL_Log("Failed to load rectangle in FoulButton.h");
        return false;
    }
    rectangle.setStretching(gButtonRect.w, gButtonRect.h);
    return true;
}

void FoulButton::setDefaultFoul(int value)
{
    defaultFouls = value;

    iteratorFouls = value;
    // Ratio always >2
    int icon_ratio = 64;
    int cWidth = icon_ratio * defaultFouls;
    int cHeight = icon_ratio;
    center_rect.w = cWidth;
    center_rect.h = cHeight;
    for (int i = 0; i < STATE_TOTAL; i++)
        icon[i].setStretching(icon_ratio, icon_ratio);
}

void FoulButton::increaseFoul(int value)
{
    if (iteratorFouls - value < 0 || iteratorFouls - value > defaultFouls)
    {
        SDL_Log("Error to change iterator fouls in FoulButton.h");
        return;
    }
    iteratorFouls -= value;
}
bool FoulButton::lose()
{
    return iteratorFouls == 0;
}

void FoulButton::draw(SDL_Renderer *Foul_Renderer)
{
    center_rect.x = gButtonRect.x + (gButtonRect.w - center_rect.w) / 2;
    center_rect.y = gButtonRect.y + (gButtonRect.h - center_rect.h) / 2;
    rectangle.render(Foul_Renderer, gButtonRect.x, gButtonRect.y);
    // SDL_Log("%d %d %d %d",gButtonRect.x,gButtonRect.y,gButtonRect.w,gButtonRect.h);
    SDL_SetRenderDrawColor(Foul_Renderer, 145, 255, 190, 0);
    SDL_RenderFillRect(Foul_Renderer, &center_rect);
    for (int i = 0; i < iteratorFouls; i++)
    {
        icon[FULL].render(Foul_Renderer, center_rect.x + icon[FULL].getWidth() * i, center_rect.y);
    }
    for (int i = iteratorFouls; i < defaultFouls; i++)
    {
        icon[EMPTY].render(Foul_Renderer, center_rect.x + icon[EMPTY].getWidth() * i, center_rect.y);
    }
}
void FoulButton::destroy()
{
    for (int i = 0; i < STATE_TOTAL; i++)
        icon[i].destroy();
    rectangle.destroy();
}
