#include"GTest.h"

void Text_Test(char*path, unsigned ptsize, char*str)
{
    Text *t;
    TextCache *cache;
    //
    double fps;
    double time;
    int fps_i;
    //
    SDL_Window *w;
    SDL_Renderer *r;
    SDL_Event e;

    graphical_init();


    w = SDL_CreateWindow(
        "Testing Text struct...",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1028,
        512,
        SDL_WINDOW_RESIZABLE
    );
    r = SDL_CreateRenderer(
        w,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    cache = TextCache_Create(r, path, ptsize);
    t = Text_Create(cache);
    Text_SetUTF8(t, str);

    *Text_wrap(t) = 1024;
    *Text_scaleWidth(t) = *Text_scaleHeight(t) = 1 / 2.0;
    fps = 0;
    fps_i = 1;
    time = SDL_GetTicks();
    while(1){
        // printf("FPS: %.2lf\n", fps / (fps_i));
        SDL_SetRenderDrawColor(r, 255, 255, 0, 255);
        SDL_RenderClear(r);
        *Text_chrRotation(t) = 270;
        *Text_chrFlip(t) = SDL_FLIP_HORIZONTAL;
        *Text_y(t) = 500;
        *Text_rotation(t) = 90;
        *Text_flip(t) = SDL_FLIP_VERTICAL;
        //*
        Text_DrawUTF8(
            t,
            str,
            (TextConfig){
                .color=(SDL_Color){0, 0, 255, 255},
                .fmt = CHAR_FMT_REGULAR
            }
        );
        // */

        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    Text_Destroy(&t);
                    TextCache_Destroy(&cache);
                    SDL_DestroyWindow(w);
                    SDL_DestroyRenderer(r);
                    SDL_Quit();
                    exit(0);
                    break;

                default:
                    break;
            }
        }

        ++fps_i;
        if(fps_i >= FPS_I){
            fps = 0;
            fps_i = 1;
        }
        fps += 1000.0 / (SDL_GetTicks() - time);
        time = SDL_GetTicks();

        SDL_RenderPresent(r);
        SDL_Delay(GTEST_DELAY);
    }
}
