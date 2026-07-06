#include"main.h"

//
int main()
{
    SDL_Event e;

    graphical_init();
    Window_init(&app);
    Bullet_init(&bullet, &app);
    while(1){
        Window_render(&app);
        Bullet_render(&bullet);
        while(SDL_PollEvent(&e)){
            Bullet_event(&bullet, e);
            Window_event(&app, e);
        }
        Window_present(&app);
        // printf("%i %i\n", *Shot_vx(&bullet), *Shot_vy(&bullet));
        SDL_Delay(SDL_DELAY);
    }
    return 0;
}
