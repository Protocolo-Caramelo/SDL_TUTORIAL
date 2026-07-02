#ifndef SDL_WIN_H
#define SDL_WIN_H

#include<graphical_init.h>
#include<graphical_winConsts.h>

#include<SDL2/SDL.h>
#include<string.h>

//
typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
} Win;

// Setters
void Win_renderer_def(Win*, SDL_Renderer*);
void Win_window_def(Win*, SDL_Window*);

// Getters
SDL_Renderer *Win_renderer(const Win*);
SDL_Window *Win_window(const Win*);


// Methods
void Win_init(Win*);
void Win_render(Win*);
void Win_cleanup(Win*);

#endif
