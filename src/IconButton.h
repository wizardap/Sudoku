#ifndef ICONBUTTON_H
#define ICONBUTTON_H
#include "Button.h"
#include "Texture.h"
class IconButton : public Button
{
public:
    IconButton();
    ~IconButton();
    IconButton(SDL_Rect rect);
    bool init(SDL_Renderer* Button_Renderer,std::string path);
    void draw(SDL_Renderer* Button_Renderer);
    void update(SDL_Event e);
    void destroy();
    bool isInside(int x,int y);
    int getWidth();
    int getHeight();
    enum State
    {
        MOUSE_OUT,
        MOUSE_IN,
        MOUSE_DOWN,
        MOUSE_UP,
        TOTAL
    };
    State CurrentState;
    Texture gTexture[TOTAL];

};
#endif // ICONBUTTON_H
