#include "Options.h"






/// Option library
Options::Options()
{
    muted=false;
    CurrentState = Options::NONE;
    gButtonRect = {780,600,220,80};
}

Options::~Options()
{
    destroy();
}

bool Options::init(SDL_Renderer* Option_Renderer)
{
    if (!option[Options::NEWGAME].init(Option_Renderer,"assets/Options/NewGame"))
    {
        SDL_Log("Failed to load NEWGAME button in Option.cpp");
        return false;
    }
    if (!option[Options::SURRENDER].init(Option_Renderer,"assets/Options/Surrender"))
    {
        SDL_Log("Failed to load SURRENDER button in Option.cpp");
        return false;
    }
    if (!option[Options::EXIT].init(Option_Renderer,"assets/Options/Exit"))
    {
        SDL_Log("Failed to load EXIT button in Option.cpp");
        return false;
    }
    if (!option[Options::SOUND_OFF].init(Option_Renderer,"assets/Options/Sound_Off"))
    {
        SDL_Log("Failed to load SOUND_OFF button in Option.cpp");
        return false;
    }
    if (!option[Options::SOUND_ON].init(Option_Renderer,"assets/Options/Sound_On"))
    {
        SDL_Log("Failed to load SOUND_ON button in Option.cpp");
    }
    int icon_ratio = 64;
    int distanceOf2Icons = 10;
    for (int i=1; i<Options::TOTAL-1; i++)
    {
        option[i].setRect({gButtonRect.x + (distanceOf2Icons+option[i].getWidth())*(i-1),gButtonRect.y,icon_ratio,icon_ratio});
        if (i==Options::TOTAL-2)
            option[i+1].setRect({gButtonRect.x + (distanceOf2Icons+option[i].getWidth())*(i-1),gButtonRect.y,icon_ratio,icon_ratio});
    }
    return true;
}

void Options::update(SDL_Event e)
{
    for (int i=1; i<Options::TOTAL; i++)
    {
        option[i].update(e);
    }
    if (option[Options::NEWGAME].isSelected())
    {
        CurrentState = Options::NEWGAME;
    }
    else if (option[Options::EXIT].isSelected())
    {
        CurrentState = Options::EXIT;
    }
    else if (option[Options::SURRENDER].isSelected())
    {
        CurrentState = Options::SURRENDER;
    }
    else if (option[Options::SOUND_ON].isSelected())
    {
        muted=!muted;
        if (muted)
        {

            CurrentState = Options::SOUND_OFF;
        }
        else
        {

            CurrentState = Options::SOUND_ON;
        }

    }
    else CurrentState = NONE;
}

void Options::draw(SDL_Renderer* Options_Renderer)
{

    for (int i =1; i<Options::TOTAL-2; i++)
            option[i].draw(Options_Renderer);
    if (muted) option[SOUND_OFF].draw(Options_Renderer);
    else option[SOUND_ON].draw(Options_Renderer);
}
void Options::resetState()
{
    CurrentState = NONE;
}

void Options::destroy()
{
    for (int i =0; i<Options::TOTAL; i++)
        option[i].destroy();
}
