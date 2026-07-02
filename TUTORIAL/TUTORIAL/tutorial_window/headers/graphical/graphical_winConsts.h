#ifndef SDL2_WINCONSTS
#define SDL2_WINCONSTS

#include<SDL2/SDL.h>

/*
 * Window default dimensions
 */
// Default width for window in px
#define WIN_DEFAULT_WIDTH 1280
// Default height for window in px
#define WIN_DEFAULT_HEIGHT 580

/*
 * Window default behavior
 */
// Let OS set the initial position for new window
#define WIN_DEFAULT_POS_X SDL_WINDOWPOS_UNDEFINED
#define WIN_DEFAULT_POS_Y SDL_WINDOWPOS_UNDEFINED

/*
 * Window's default flags 
 */
#define WIN_DEFAULT_RENDERER_FLAGS SDL_RENDERER_ACCELERATED
#define WIN_DEFAULT_WINDOW_FLAGS 0

#endif
