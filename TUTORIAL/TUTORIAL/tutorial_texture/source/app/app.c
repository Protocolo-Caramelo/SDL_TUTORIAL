#include"app.h"

Window app;

void App_initialize()
{
    graphical_init();

    memset(&app, 0, sizeof(app));
    Window_raw_def(
        &app,
        SDL_CreateWindow("Texture Tutorial", APP_INIT_X, APP_INIT_Y, APP_INIT_WIDTH, APP_INIT_HEIGHT, APP_INIT_WINDOW_FLAGS)
    );
    if(!Window_raw(&app)){
        printf("Error in app window initialization: %s\n", SDL_GetError());
        exit(1);
    }

    Window_renderer_def(
        &app,
        SDL_CreateRenderer(Window_raw(&app), -1, APP_INIT_RENDERER_FLAGS)
    );
    if(!Window_renderer(&app)){
        printf("Error in app renderer initialization: %s\n", SDL_GetError());
        exit(1);
    }
}

void App_destroy()
{
    SDL_DestroyRenderer(Window_renderer(&app));
    SDL_DestroyWindow(Window_raw(&app));
    SDL_Quit();
}

void App_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                App_destroy();
                exit(0);
                break;

            default:
                break;
        }
    }
}

void App_render()
{
    SDL_SetRenderDrawColor(Window_renderer(&app), 255, 255, 0, 255);
    SDL_RenderClear(Window_renderer(&app));
}

void App_present()
{
    SDL_RenderPresent(Window_renderer(&app));
}

void doApp()
{
    App_initialize();
    Entity_initialize();
    while(1){
        App_render();
        Entity_render();

        App_events();
        Entity_events();

        App_present();
        SDL_Delay(16);
    }
}
