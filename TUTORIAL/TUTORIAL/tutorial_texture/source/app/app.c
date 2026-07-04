#include"app.h"

Window app;

void App_initialize()
{
    graphical_init();
    memset(&app, 0, sizeof(app));

    SDL_Window **app_w;
    SDL_Renderer **app_r;
    app_w = Window_raw(&app);
    app_r = Window_renderer(&app);

    *app_w = SDL_CreateWindow("Texture Tutorial", APP_INIT_X, APP_INIT_Y, APP_INIT_WIDTH, APP_INIT_HEIGHT, APP_INIT_WINDOW_FLAGS);
    if(!*app_w){
        printf("Error in app window initialization: %s\n", SDL_GetError());
        exit(1);
    }

    *app_r = SDL_CreateRenderer(*app_w, -1, APP_INIT_RENDERER_FLAGS);
    if(!*app_r){
        printf("Error in app renderer initialization: %s\n", SDL_GetError());
        exit(1);
    }
}

void App_destroy()
{
    SDL_DestroyRenderer(*Window_renderer(&app));
    SDL_DestroyWindow(*Window_raw(&app));
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
    SDL_SetRenderDrawColor(*Window_renderer(&app), 255, 255, 0, 255);
    SDL_RenderClear(*Window_renderer(&app));
}

void App_present()
{
    SDL_RenderPresent(*Window_renderer(&app));
}

void doApp()
{
    srand(time(0));
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
