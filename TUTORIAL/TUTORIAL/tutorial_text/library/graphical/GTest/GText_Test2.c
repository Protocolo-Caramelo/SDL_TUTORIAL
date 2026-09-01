#ifdef COMPILATION_DEVQUOTE
#include"GTest.h"

typedef enum AngleState {
    ANGLE_REDUCE,
    ANGLE_INCREASE,
} AngleState;

double radius;
double angle;
int position;
//
double minus;
double minusTax = 0.05;
AngleState angleState;

void AlterFunc_TextDrawUTF8(Text*t, TextChar*c)
{
    if(c->idx == 0){
        radius = 300;
        angle = 0;
        position = 0;
        // c->x = -radius;
    }

    c->x = -radius * cos(DEG_TO_RAD(angle));
    c->y = -radius * sin(DEG_TO_RAD(angle));

    angle += 360.0 / (Text_GetSizeUTF8(t));
    ++position;
    radius += minus;
}

void Text_Test2(char*fpath, unsigned ptsize, char*str)
{
    Text *t;
    TextCache *cache;
    //
    double fps;
    double fps_delay;
    unsigned fps_time;
    unsigned fps_delayTime;
    //
    extern double minus;
    //
    SDL_Window *w;
    SDL_Renderer *r;
    SDL_Event e;

    graphical_init();
    w = SDL_CreateWindow(
        "2nd test of Text struct",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        512,
        SDL_WINDOW_RESIZABLE
    );
    r = SDL_CreateRenderer(
        w,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    cache = TextCache_Create(r, fpath, ptsize);
    t = Text_Create(cache);
    //
    fps_delay = 100;
    fps_delayTime = fps_time = SDL_GetTicks();
    //
    minus = 0;

    while(1){
        SDL_SetRenderDrawColor(r, 100, 100, 255, 255);
        SDL_RenderClear(r);

        if(SDL_GetTicks() - fps_delayTime >= fps_delay){
            printf("FPS: %.2lf\n", fps);
            fps_delayTime = SDL_GetTicks();
        }

        //*
        Text_DrawUTF8(
            t,
            str,
            TextConfig_Create(
                .color = (SDL_Color){155, 155, 0, 255},
                .scale_width = 1 / 2.0,
                .scale_height = 1 / 2.0,
                .wrap = 1024,
                .x = 100,
                .y = 0,
            ),
            &AlterFunc_TextDrawUTF8
            // NULL
        );
        // */

        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    SDL_DestroyWindow(w);
                    SDL_DestroyRenderer(r);
                    SDL_Quit();

                    exit(0);

                default:
                    break;
            }
        }

        SDL_RenderPresent(r);
        SDL_Delay(GTEST_DELAY);

        fps = 1000.0 / (SDL_GetTicks() - fps_time);
        fps_time = SDL_GetTicks();
        //
        if(angleState == ANGLE_REDUCE){
            minus -= minusTax;
        }
        else if(angleState == ANGLE_INCREASE){
            minus += minusTax;
        }

        if(minus <= - 10){
            angleState = ANGLE_INCREASE;
        }
        else if(minus >= 0){
            angleState = ANGLE_REDUCE;
        }
    }
}

#endif
