#include"main.h"

//
int main()
{
    SDL_Event e;
    T_TIMESTAMP t;

    graphical_init();
    App_init(&app);
    Guideline_init(&guideline);
    Balls_init();
    t = SDL_GetTicks();
    while(1){
        App_render(&app);
        Balls_render();
        Guideline_render(&guideline);

        while(SDL_PollEvent(&e)){
            App_event(&app, e);
            Balls_event(e);
            Guideline_event(&guideline, e);
        }

        App_present(&app);
        SDL_Delay(DELAY_PER_FRAME);
        // printf("%lf\n", 1000.0 / (SDL_GetTicks() - t));
        t = SDL_GetTicks();
    }
    return 0;
}
