#include "NoticeWindow.h"

NoticeWindow::NoticeWindow()
{
    gWindowRect = {780,200,256,256};
    gCurrentState = WAITING;
}

NoticeWindow::~NoticeWindow()
{
    destroy();
}
void NoticeWindow::draw(SDL_Renderer* Notice_Renderer)
{
    gImageRect.render(Notice_Renderer,gWindowRect.x,gWindowRect.y);
    gText[gCurrentState]->drawText(Notice_Renderer,
                                   gWindowRect.x + (gWindowRect.w - gText[gCurrentState]->getWidth())/2,
                                   gWindowRect.y + (gWindowRect.h - gText[gCurrentState]->getHeight())/2);
}

void NoticeWindow::destroy()
{
    for (int i =0; i<4; i++)
        gText[i]->destroy();
    gImageRect.destroy();
}

bool NoticeWindow::init(SDL_Renderer* Notice_Renderer)
{
    for (int i =0; i<TOTAL; i++)
        gText[i] = new DynamicText(FontManager->getFont(fontfilepath,20));
    if (gText[WAITING]->loadText(Notice_Renderer,"Waiting...", {0,0,0,0})==false)
    {
        SDL_Log("Failed to load WAITING text in NoticeWindow.h");
        return false;
    }
    if (gText[NICETURN]->loadText(Notice_Renderer,"Nice turn!", {0,0,0,0})==false)
    {
        SDL_Log("Failed to load NICETURN text in NoticeWindow.h");
        return false;
    }
    if (gText[WRONG]->loadText(Notice_Renderer,"WRONG!", {0,0,0,0})==false)
    {
        SDL_Log("Failed to load WRONG text in NoticeWindow.h");
        return false;
    }
    if (gText[GAMEOVER]->loadText(Notice_Renderer,"Game Over!", {0,0,0,0})==false)
    {
        SDL_Log("Failed to load Game Over text in NoticeWindow.h");
        return false;
    }
    if (gText[WINNING]->loadText(Notice_Renderer,"You won !", {0,0,0,0})==false)
    {
        SDL_Log("Failed to load WINNING text in NoticeWindow.h");
        return false;
    }
    if (gImageRect.loadImage(Notice_Renderer,"assets/Notice/notice.png")==false)
    {
        SDL_Log("Failed to load notice rectangle in NoticeWindow.cpp");
        return false;
    }
    gImageRect.setStretching(gWindowRect.w,gWindowRect.h);
    return true;
}
void NoticeWindow::waiting()
{
    gCurrentState = WAITING;
}

void NoticeWindow::niceturn()
{
    gCurrentState = NICETURN;
}

void NoticeWindow::wrong()
{
    gCurrentState=WRONG;
}

void NoticeWindow::gameover()
{
    gCurrentState =GAMEOVER;
}


void NoticeWindow::winning()
{
    gCurrentState = WINNING;
}
