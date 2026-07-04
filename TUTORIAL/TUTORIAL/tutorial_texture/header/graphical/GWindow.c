#include<GWindow.h>

SDL_Renderer **Window_renderer(const Window*w)
{
    return &w->renderer;
}

SDL_Window **Window_raw(const Window*w)
{
    return &w->window;
}
