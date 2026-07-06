#include"main.h"

const WindowVTable app_vtable = {
    .init = &App_init,
    .exit = &App_exit,
    .render = &App_render,
    .present = &App_present,
    .event = &App_event
};

Window app = {
    .vtable = app_vtable
};

//
void App_init(Window*app)
{
    SDL_Window **app_window;
    SDL_Renderer **app_renderer;

    app_window = Window_raw(app);
    app_renderer = Window_renderer(app);

    *app_window = SDL_CreateWindow(
        "Tutorial Keys",
        APP_INIT_XPOS,
        APP_INIT_YPOS,
        APP_INIT_WIDTH,
        APP_INIT_HEIGHT,
        APP_INIT_WINDOWFLAGS
    );
    if(!*app_window){
        printf("Error while initializing app's window: %s\n", SDL_GetError());
        exit(1);
    }

    *app_renderer = SDL_CreateRenderer(
        *app_window,
        -1,
        APP_INIT_RENDERERFLAGS
    );
    if(!*app_renderer){
        printf("Error while initializing app's renderer: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetRenderDrawColor(
        *app_renderer,
        0,
        255,
        255,
        255
    );
}

void App_exit(Window*app)
{
    SDL_DestroyRenderer(*Window_renderer(app));
    SDL_DestroyWindow(*Window_raw(app));

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}

void App_render(Window*app)
{
    SDL_RenderClear(*Window_renderer(app));
}

void App_present(Window*app)
{
    SDL_RenderPresent(*Window_renderer(app));
}

void App_event(Window*app, SDL_Event e)
{
    switch(e.type){
        case SDL_QUIT:
            Window_exit(app);
            exit(0);
            break;

        default:
            break;
    }
}
