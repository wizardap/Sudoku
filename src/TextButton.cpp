#include "TextButton.h"

TextButton::TextButton()
{
    CurrentState = MOUSE_OUT;
    gColor[MOUSE_OUT] = {0,0,0,0};
    gColor[MOUSE_IN] = {204, 204, 204,0};
    gColor[MOUSE_DOWN] = {127, 127, 127,0};
    gColor[MOUSE_UP] = gColor[MOUSE_IN];
}

TextButton::~TextButton()
{
    destroy();
}
TextButton::TextButton(SDL_Rect rect)
{
    gButtonRect = rect;
}

bool TextButton::init(SDL_Renderer* Button_Renderer,std::string name_button)
{
    gText = new DynamicText(FontManager->getFont("Bungee-Regular.ttf",20));
    gName = name_button;
    gText->loadText(Button_Renderer,gName,gColor[CurrentState]);
    gButtonRect.w = gText->getWidth();
    gButtonRect.h = gText->getHeight();
    return true;
}

void TextButton::draw(SDL_Renderer* Button_Renderer)
{
    gText->loadText(Button_Renderer,gName,gColor[CurrentState]);
    gText->drawText(Button_Renderer,gButtonRect.x,gButtonRect.y);
}
bool TextButton::isInside(int x, int y)
{
    return (x>=gButtonRect.x &&
            y>=gButtonRect.y &&
            x<=gButtonRect.x + gButtonRect.w &&
            y<=gButtonRect.y + gButtonRect.h);
}

void TextButton::update(SDL_Event e)
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



void TextButton::destroy()
{
    gText->destroy();
    gName.clear();
}
int TextButton::getWidth()
{
    return gButtonRect.w;
}

int TextButton::getHeight()
{
    return gButtonRect.h;
}
