#ifndef DYNAMICTEXT_H_
#define DYNAMICTEXT_H_
#include<SDL_ttf.h>
#include<SDL.h>
#include<string>
#include "Texture.h"
class DynamicText
{
public:
    DynamicText(std::string fontfilepath,size_t fontSize);
    virtual ~DynamicText();
    void drawText(SDL_Renderer* Text_Renderer,int x,int y);
    bool loadText(SDL_Renderer* Text_Renderer,std::string text,SDL_Color color);
    void drawText(SDL_Renderer* Text_Renderer,std::string text,SDL_Color color,int x,int y);
    int getWidth();
    int getHeight();
    bool initialized;
private:
    Texture gTexture;
    TTF_Font* gFont;

};

#endif // DYNAMICTEXT_H_
