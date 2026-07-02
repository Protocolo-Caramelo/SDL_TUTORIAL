#include<graphical_win.h>

// Setters
void Win_renderer_def(Win*w, SDL_Renderer*r)
{
    w->renderer = r;
}

void Win_window_def(Win*w, SDL_Window*win)
{
    w->window = win;
}

// Getters
SDL_Renderer* Win_renderer(const Win*w)
{
    return w->renderer;
}

SDL_Window* Win_window(const Win*w)
{
    return w->window;
}

// Methods
void Win_init(Win*w)
{
    memset(w, 0, sizeof(Win));

    if(!graphical_video_initialized)
    {
        printf("Can't initalize window because SDL VIDEO doesn't has been initialized\n");
        exit(1);
    }

    Win_window_def(w, SDL_CreateWindow("Window Tutorial", WIN_DEFAULT_POS_X, WIN_DEFAULT_POS_Y, WIN_DEFAULT_WIDTH, WIN_DEFAULT_HEIGHT, WIN_DEFAULT_WINDOW_FLAGS));
    if(!Win_window(w)){
        printf("Fail to create window: %s\n", SDL_GetError());
        exit(1);
    }
    Win_renderer_def(w, SDL_CreateRenderer(Win_window(w), -1, WIN_DEFAULT_RENDERER_FLAGS));
    if(!Win_renderer(w)){
        printf("Fail to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void Win_render(Win*w)
{
    SDL_RenderPresent(Win_renderer(w));
}

void Win_cleanup(Win*w)
{
    SDL_DestroyRenderer(Win_renderer(w));
    SDL_DestroyWindow(Win_window(w));
}
