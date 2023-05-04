#include "Button.h"

Button::Button()
{
    locked=false;
    selected=false;
    gButtonRect = {0,0,0,0};
}

Button::~Button()
{
    locked=false;
    selected=false;
    gButtonRect = {0,0,0,0};
}

void Button::setRect(SDL_Rect rect)
{
    gButtonRect = rect;
}

void Button::setLocking(bool lock)
{
    locked = lock;
}

void Button::setSelecting(bool select)
{
    selected = select;
}


bool Button::isLocked()
{
    return locked;
}

bool Button::isSelected()
{
    return selected;
}
