#include "Texture.h"

Texture::Texture()
    :mTexture(NULL),
     mWidth(0),
     mHeight(0)
{

}

Texture::~Texture()
{
    destroy();
}

bool Texture::loadImage(SDL_Renderer* renderer, std::string path)
{
    destroy();
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface==NULL)
    {
        SDL_Log("Surface could not be created ! IMG Error :%s\n",IMG_GetError());
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
    if (mTexture == NULL)
    {
        SDL_Log("Texture could not be created ! SDL Error: %s\n",SDL_GetError());
        return false;
    }
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);
    return true;
}

bool Texture::loadText(SDL_Renderer* renderer, TTF_Font* font, std::string textInput, SDL_Color textColor)
{
    destroy();
    SDL_Surface *textSurface = TTF_RenderText_Solid(font,textInput.c_str(),textColor);
    if (textSurface==NULL)
    {
        SDL_Log("Surface could not be created ! IMG Error :%s\n",IMG_GetError());
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
    if (mTexture == NULL)
    {
        SDL_Log("Texture could not be created ! SDL Error: %s\n",SDL_GetError());
        return false;
    }
    mWidth = textSurface->w;
    mHeight = textSurface->h;

    SDL_FreeSurface(textSurface);
    return true;
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect des = {x,y,mWidth,mHeight};
    if (clip!=NULL)
    {
        des.w = clip->w;
        des.h = clip->h;
    }
    SDL_RenderCopyEx(renderer,mTexture,clip,&des,angle,center,flip);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture,blending);
}

void Texture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture,alpha);
}

void Texture::destroy()
{
    SDL_DestroyTexture(mTexture);
    mTexture=NULL;
    mWidth =0;
    mHeight=0;
}


int Texture::getWidth()
{
    return mWidth;
}

int Texture::getHeight()
{
    return mHeight;
}
