#ifndef NOTICEWINDOW_H
#define NOTICEWINDOW_H

#include "DynamicText.h"
#include "Texture.h"
#include "SDK_ults.h"

class NoticeWindow
{
public:
    NoticeWindow();
    virtual ~NoticeWindow();
    void draw(SDL_Renderer* Notice_Renderer);
    void destroy();
    bool init(SDL_Renderer* Notice_Renderer);
    void waiting();
    void niceturn();
    void wrong();
    void gameover();
    void winning();
protected:

private:
    enum NoticeState
    {
        WAITING,
        NICETURN,
        WRONG,
        WINNING,
        GAMEOVER,
        TOTAL
    };
    NoticeState gCurrentState;
    SDL_Rect gWindowRect;
    Texture gImageRect;
    DynamicText* gText[TOTAL];
    const std::string fontfilepath = "Bungee-Regular.ttf";
};

#endif // NOTICEWINDOW_H
