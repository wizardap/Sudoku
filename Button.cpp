#include "Button.h"

Button::Button():
{
    //ctor
}

Button::~Button()
{
    //dtor
}

void Button::renderButton(SDL_Renderer* Button_Renderer)
{

}

ButtonState Button::getMouseState(SDL_Event e)
{
    int x,y;
    SDL_GetMouseState(&x,&y);
    ButtonState currentState = BUTTON_MOUSE_OUT;
    if (isMouseInside(x,y))
        currentState = BUTTON_MOUSE_IN;
    else if (e.button.button == SDL_MOUSEBUTTONDOWN)
    {
        currentState = BUTTON_MOUSE_DOWN;
    }
    return currentState;
}

bool Button::isClicked()
{
    return clicked;
}


bool Button::isMouseInside(int x,int y)
{
    return (x<gButtonRect.x||
            x>gButtonRect.x + gButtonRect.w ||
            y<gButtonRect.y ||
            y>gButtonRect.y + gButtonRect.h);
}

void Button::setButtonRect(SDL_Rect rect)
{
    gButtonRect = rect;

}

