#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "Button.h"
#include "DynamicText.h"
#include "SDK_ults.h"

class TextButton : public Button
{
public:
    TextButton();
    ~TextButton();
    TextButton(SDL_Rect rect);
    bool init(SDL_Renderer* Button_Renderer,std::string name_button);
    void draw(SDL_Renderer* Button_Renderer);
    void update(SDL_Event e);
    void destroy();
    bool isInside(int x,int y);
    int getWidth();
    int getHeight();
private:
    enum State
    {
        MOUSE_OUT,
        MOUSE_IN,
        MOUSE_DOWN,
        MOUSE_UP,
        TOTAL
    };
    State CurrentState;
    SDL_Color gColor[TOTAL];
    std::string gName;
    DynamicText* gText;

};

#endif // TEXTBUTTON_H
