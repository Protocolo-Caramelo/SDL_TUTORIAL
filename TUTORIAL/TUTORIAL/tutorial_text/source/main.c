#include"main.h"

//
int main()
{
    SDL_Event e;

    graphical_init();
    App_init(&app);
    Guideline_init(&guideline);
    Balls_init();
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
        SDL_Delay(16);
    }
    return 0;
}
