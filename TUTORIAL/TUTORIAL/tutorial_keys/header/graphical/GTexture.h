#ifndef GTEXTURE_H
#define GTEXTURE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

typedef struct Texture Texture;

struct Texture{
    SDL_Texture *raw;
    SDL_Renderer *renderer;
};

static inline SDL_Texture** Texture_raw(Texture*t)
{
    return &t->raw;
}

static inline SDL_Renderer** Texture_renderer(Texture*t)
{
    return &t->renderer;
}

void Texture_loadFromImg(Texture*to, const char*path);

#endif
