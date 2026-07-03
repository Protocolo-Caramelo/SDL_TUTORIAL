#include<GWindow.h>

void Window_renderer_def(Window*w, SDL_Renderer*r)
{
    w->renderer = r;
}

void Window_raw_def(Window*w, SDL_Window*win)
{
    w->window = win;
}


SDL_Renderer *Window_renderer(const Window*w)
{
    return w->renderer;
}

SDL_Window *Window_raw(const Window*w)
{
    return w->window;
}
