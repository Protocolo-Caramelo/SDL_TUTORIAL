#ifndef APP_H
#define APP_H

#include<graphical.h>

#define APP_INIT_XPOS SDL_WINDOWPOS_UNDEFINED
#define APP_INIT_YPOS SDL_WINDOWPOS_UNDEFINED
#define APP_INIT_WIDTH 900
#define APP_INIT_HEIGHT 450
#define APP_INIT_WINDOWFLAGS (SDL_WINDOW_RESIZABLE)
#define APP_INIT_RENDERERFLAGS (SDL_RENDERER_ACCELERATED)

void App_init(Window*);
void App_exit(Window*);
void App_render(Window*);
void App_present(Window*);
void App_event(Window*, SDL_Event);

extern const WindowVTable app_vtable;
extern Window app;

#endif
