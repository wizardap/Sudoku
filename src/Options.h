#ifndef OPTIONS_H
#define OPTIONS_H
#include "Button.h"
#include "IconButton.h"

class Options : public Button
{
public:
    enum OptionState
    {
        NONE,
        NEWGAME,
        EXIT,
        SURRENDER,
        SOUND_OFF,
        SOUND_ON,
        TOTAL
    };
    Options();
    virtual ~Options();
    bool init(SDL_Renderer* Option_Renderer);
    void update(SDL_Event e);
    void draw(SDL_Renderer* Options_Renderer);
    void resetState();
    void destroy();
    OptionState CurrentState;
private:
    bool muted;
    IconButton option[TOTAL];

};

#endif // OPTIONS_H
