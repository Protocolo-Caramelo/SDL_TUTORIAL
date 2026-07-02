#include"app.h"

Win app;

void App_set_color(Win*app)
{
    int red, green, blue;
    srand(time(0));

    red = rand() % 256;
    green = rand() % 256;
    blue = rand() % 256;
    SDL_SetRenderDrawColor(Win_renderer(app), red, green, blue, 255);
    SDL_RenderClear(Win_renderer(app));
}

void App_events(Win*app)
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                Win_cleanup(app);
                exit(0);
                break;

            default:
                break;
        }
    }
}

void App_present(Win*app)
{
    Win_render(app);
}

//
void doApp()
{
    extern Win app;

    graphical_setup();
    Win_init(&app);
    while(1){
        App_set_color(&app);
        App_events(&app);
        App_present(&app);

        SDL_Delay(16);
    }
}
