#include"GTest.h"

void Text_Test(char*path, unsigned ptsize, char*str)
{
    Text *t;
    TextCache *cache;
    //
    double fps;
    unsigned time;
    int fps_delay;
    //
    double chrRotation;
    int chrRotation_delay;
    int chrFmt;
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
    *Text_scaleWidth(t) = *Text_scaleHeight(t) = 1 / 5.0;
    //
    fps = 0;
    fps_delay = SDL_GetTicks();
    time = SDL_GetTicks();
    //
    chrRotation_delay = 0;
    chrRotation = 0;
    chrFmt = 0;
    while(1){
        if((SDL_GetTicks() - fps_delay) >= FPS_DELAY){
            printf("FPS: %.2lf\n", fps);
            fps_delay = SDL_GetTicks();
        }
        // printf("%lf\n", chrRotation);

        // printf("%s %lf\n", str, chrRotation);
        if((SDL_GetTicks() - chrRotation_delay) >= ROTATION_DELAY){
            chrRotation_delay = SDL_GetTicks();
            chrRotation = 0;
            // ++chrFmt;
            chrFmt %= (CHAR_FMT_REGULAR | CHAR_FMT_BOLD | CHAR_FMT_ITALIC | CHAR_FMT_UNDERLINE | CHAR_FMT_STRIKETHROUGH);
        };

        SDL_SetRenderDrawColor(r, 255, 255, 0, 255);
        SDL_RenderClear(r);
        //*
        Text_DrawUTF8(
            t,
            str,
            (TextConfig){
                .color=(SDL_Color){0, 0, 255, 255},
                .fmt = chrFmt,
                .chr_rotation = chrRotation,
                // .chr_rotation = 324,
                .rotation = 0
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

        SDL_RenderPresent(r);
        SDL_Delay(GTEST_DELAY);

        fps = 1000.0 / (SDL_GetTicks() - time);
        //chrRotation += (360.0 / ROTATION_DELAY) * (SDL_GetTicks() - time);
        chrRotation += 360.0 / (ROTATION_DELAY / GTEST_DELAY);
        time = SDL_GetTicks();
    }
}
