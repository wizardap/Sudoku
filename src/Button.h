#ifndef BUTTON_H
#define BUTTON_H
#include <SDL2/SDL.h>

class Button
{
public:
    Button();
    virtual ~Button();
    void setRect(SDL_Rect rect);
    void setLocking(bool lock = false);
    void setSelecting(bool select = false);
    bool isLocked();
    bool isSelected();

protected:
    bool locked;
    bool selected;
    SDL_Rect gButtonRect;
};

#endif // BUTTON_H
