#include "DynamicText.h"

DynamicText::DynamicText(std::string fontfilepath, size_t fontSize)
{
    if (!initialized && TTF_Init() <0)
    {
        SDL_Log("Dynamic Text could not initialize TTF_Font , TTF Error : %s",TTF_GetError());
    }
    else
    {
        gFont = TTF_OpenFont(fontfilepath.c_str(),fontSize);
        if (gFont == NULL)
        {
            SDL_Log("%s could not open! TTF Error :%s",fontfilepath.c_str(),TTF_GetError());
        }
        else
        {
            initialized = true;
        }
    }
}

DynamicText::~DynamicText()
{
    gTexture.destroy();
    TTF_CloseFont(gFont);
}

void DynamicText::drawText(SDL_Renderer* Text_Renderer,int x,int y)
{
    gTexture.render(Text_Renderer,x,y);
}
void DynamicText::drawText(SDL_Renderer* Text_Renderer, std::string text, SDL_Color color, int x, int y)
{
    if (gTexture.loadText(Text_Renderer,gFont,text,color)==false)
    {
        SDL_Log("Text could not load! Error on DynamicText class!");
        return;
    }
    gTexture.render(Text_Renderer,x,y);
}

bool DynamicText::loadText(SDL_Renderer* Text_Renderer, std::string text, SDL_Color color)
{
    if (gTexture.loadText(Text_Renderer,gFont,text,color)==false)
    {
        SDL_Log("Text could not load! Error on DynamicText class!");
        return false;
    }
    return true;
}

int DynamicText::getWidth()
{
    return gTexture.getWidth();
}

int DynamicText::getHeight()
{
    return gTexture.getHeight();
}
