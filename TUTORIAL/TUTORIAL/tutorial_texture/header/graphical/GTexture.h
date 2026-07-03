#ifndef GTEXTURE_H
#define GTEXTURE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdint.h>

typedef int16_t T_COL;
typedef int16_t T_ROW;

typedef struct {
    T_COL x;
    T_ROW y;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} Texture;

void Texture_x_def(Texture*, T_COL);
void Texture_y_def(Texture*, T_ROW);
void Texture_renderer_def(Texture*, SDL_Renderer*);
void Texture_raw_def(Texture*, SDL_Texture*);

T_COL Texture_x(const Texture*);
T_ROW Texture_y(const Texture*);
SDL_Renderer*  Texture_renderer(const Texture*);
SDL_Texture* Texture_raw(const Texture*);

void Texture_loadFromIMG(Texture*to, const char*path);

#endif
