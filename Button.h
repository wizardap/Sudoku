#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"
#include "Mouse.h"
class Button
{
public:
    Button();
    virtual ~Button();
    bool isClicked();
    void renderButton(SDL_Renderer* Button_Renderer);
    bool isMouseInside(int x,int y);
    ButtonState getMouseState(SDL_Event e);
    void setButtonRect(SDL_Rect rect);
protected:
    enum ButtonState
    {
        BUTTON_MOUSE_OUT,
        BUTTON_MOUSE_IN,
        BUTTON_MOUSE_DOWN,
        BUTTON_LOCKED,
        BUTTON_TOTAL_STATES
    };
    bool clicked;
    ButtonState gCurrentState;

private:
    SDL_Rect gButtonRect;
};

#endif // BUTTON_H
