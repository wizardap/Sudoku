#include "DynamicText.h"

DynamicText::DynamicText(TTF_Font* font)
{
    gFont = font;
}
DynamicText::DynamicText()
{
    gFont = NULL;
}

DynamicText::~DynamicText()
{
    destroy();
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
void DynamicText::destroy()
{
    gTexture.destroy();
}
