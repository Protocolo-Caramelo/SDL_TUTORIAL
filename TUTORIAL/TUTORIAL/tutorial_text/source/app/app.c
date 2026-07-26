#include"main.h"

const AppVTable app_vtable = {
    .init = &AppVTable_init,
    .exit = &AppVTable_exit,
    .render = &AppVTable_render,
    .present = &AppVTable_present,
    .event = &AppVTable_event
};
App app = {
    .vtable = app_vtable
};

//
void AppVTable_init(App*app)
{
    *App_window(app) = SDL_CreateWindow(
        APP_INIT_WINDOW_NAME,
        APP_INIT_WINDOW_XPOS,
        APP_INIT_WINDOW_YPOS,
        APP_INIT_WINDOW_WIDTH,
        APP_INIT_WINDOW_HEIGHT,
        APP_INIT_WINDOW_FLAGS
    );
    if(!*App_window(app)){
        printf("Error while initializing app's window: %s\n", SDL_GetError());
        exit(1);
    }

    *App_renderer(app) = SDL_CreateRenderer(
        *App_window(app),
        -1,
        APP_INIT_RENDERER_FLAGS
    );
    if(!*App_renderer(app)){
        printf("Error while initializing app's renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void AppVTable_exit(App*app)
{
    SDL_DestroyRenderer(*App_renderer(app));
    SDL_DestroyWindow(*App_window(app));

    SDL_Quit();
}

void AppVTable_render(App*app)
{
    SDL_SetRenderDrawColor(
        *App_renderer(app),
        100,
        100,
        255,
        255
    );
    SDL_RenderClear(*App_renderer(app));
}

void AppVTable_present(App*app)
{
    SDL_RenderPresent(*App_renderer(app));
}

void AppVTable_event(App*app, SDL_Event e)
{
    switch(e.type){
        case SDL_QUIT:
            App_exit(app);
            Guideline_exit(&guideline);
            Balls_exit();
            Infos_exit();

            exit(0);
            break;

        default:
            break;
    }
}
