#ifndef SDL_WIN_H
#define SDL_WIN_H

#include<SDL2/SDL.h>
#include<string.h>

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
} Win;

void Win_init(Win*w);
void Win_cleanup(Win*w);

void Win_render(Win*w);

#endif
