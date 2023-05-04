#ifndef TIMERBUTTON_H
#define TIMERBUTTON_H

#include "Button.h"
#include "Timer.h"
#include "Texture.h"
#include "DynamicText.h"
#include "SDK_ults.h"
class TimerButton : public Button
{
public:
    TimerButton();
    virtual ~TimerButton();
    bool init(SDL_Renderer *Time_Renderer);
    void draw(SDL_Renderer *Time_Renderer);
    void start();
    void stop();
    void pause();
    void unpause();
    void destroy();
    std::string time_format();

private:
    Timer mTimer;
    DynamicText *mText;
    Texture mTexture;
};

#endif // TIMERBUTTON_H
