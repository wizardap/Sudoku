#include "IconButton.h"

IconButton::IconButton()
{
    CurrentState = MOUSE_OUT;
}

IconButton::~IconButton()
{
    destroy();
}
IconButton::IconButton(SDL_Rect rect)
{
    gButtonRect = rect;
}

bool IconButton::init(SDL_Renderer* Button_Renderer, std::string path)
{
    if (!gTexture[MOUSE_OUT].loadImage(Button_Renderer,path + "/out.png"))
    {
        SDL_Log("Failed to load MOUSE_OUT image in Options.cpp");
        return false;
    }
    if (!gTexture[MOUSE_IN].loadImage(Button_Renderer,path + "/in.png"))
    {
        SDL_Log("Failed to load MOUSE_IN image in Options.cpp");
        return false;
    }
    if (!gTexture[MOUSE_DOWN].loadImage(Button_Renderer,path + "/down.png"))
    {
        SDL_Log("Failed to load MOUSE_DOWN image in Options.cpp");
        return false;
    }
    if (!gTexture[MOUSE_UP].loadImage(Button_Renderer,path + "/up.png"))
    {
        SDL_Log("Failed to load MOUSE_UP image in Options.cpp");
        return false;
    }
    gButtonRect.w = gTexture[MOUSE_OUT].getWidth();
    gButtonRect.h = gTexture[MOUSE_OUT].getHeight();
    return true;
}

void IconButton::draw(SDL_Renderer* Button_Renderer)
{
    gTexture[CurrentState].render(Button_Renderer,gButtonRect.x,gButtonRect.y);
}
bool IconButton::isInside(int x, int y)
{
    return (x>=gButtonRect.x &&
            y>=gButtonRect.y &&
            x<=gButtonRect.x + gButtonRect.w &&
            y<=gButtonRect.y + gButtonRect.h);
}

void IconButton::update(SDL_Event e)
{
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        if (isInside(x,y))
        {
            CurrentState = MOUSE_IN;
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                CurrentState = MOUSE_DOWN;
            }
            else if (e.type == SDL_MOUSEBUTTONUP)
            {
                CurrentState = MOUSE_UP;
            }
        }
        else CurrentState = MOUSE_OUT;
    }
    else CurrentState = MOUSE_OUT;
    if (CurrentState ==MOUSE_UP) setSelecting(true);
    else setSelecting(false);
}



void IconButton::destroy()
{
    for (int i =0; i<TOTAL; i++)
        gTexture[i].destroy();
}
int IconButton::getWidth()
{
    return gButtonRect.w;
}

int IconButton::getHeight()
{
    return gButtonRect.h;
}
