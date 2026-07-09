#include"main.h"

//
int main()
{
    SDL_Event e;

    graphical_init();
    App_init(&app);
    Guideline_init(&guideline);
    while(1){
        App_render(&app);
        Guideline_render(&guideline);

        while(SDL_PollEvent(&e)){
            App_event(&app, e);
            Guideline_event(&guideline, e);
        }

        App_present(&app);
        SDL_Delay(16);
    }
    return 0;
}
