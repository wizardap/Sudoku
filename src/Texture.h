#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <string>
class Texture
{
public:
    Texture();
    virtual ~Texture();
    bool loadImage(SDL_Renderer *renderer, std::string path);
    bool loadText(SDL_Renderer *renderer, TTF_Font *font, std::string textInput, SDL_Color textColor);
    void render(SDL_Renderer *render, int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void destroy();
    void setStretching(int width, int height);
    int getWidth();
    int getHeight();
    SDL_Texture *getTexture();

private:
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
};

#endif // TEXTURE_H
