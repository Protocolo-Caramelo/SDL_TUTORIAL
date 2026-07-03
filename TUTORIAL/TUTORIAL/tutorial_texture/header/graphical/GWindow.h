#ifndef GWINDOW_H
#define GWINDOW_H

#include<SDL2/SDL.h>
#include<string.h>

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} Window;

void Window_renderer_def(Window*, SDL_Renderer*);
void Window_raw_def(Window*, SDL_Window*);

SDL_Renderer *Window_renderer(const Window*);
SDL_Window *Window_raw(const Window*);

#endif
