#ifndef GWINDOW_H
#define GWINDOW_H

#include<SDL2/SDL.h>
#include<string.h>

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} Window;

SDL_Renderer **Window_renderer(const Window*);
SDL_Window **Window_raw(const Window*);

#endif
