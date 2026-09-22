#ifdef COMPILATION_DEVQUOTE
#include"GTest.h"

#define PADDING_TOP 0x1
#define PADDING_RIGHT 0x2
#define PADDING_BOTTOM 0x4
#define PADDING_LEFT 0x8
//
#define BORDER_TOP 0x10
#define BORDER_RIGHT 0x20
#define BORDER_BOTTOM 0x40
#define BORDER_LEFT 0x80
//
#define MARGIN_TOP 0x100
#define MARGIN_RIGHT 0x200
#define MARGIN_BOTTOM 0x400
#define MARGIN_LEFT 0x800

static unsigned bitmask;

void Text_Test3(char*fpath, unsigned ptsize, char*str)
{
    SDL_Window *w;
    SDL_Renderer *r;
    SDL_Event e;
    //
    TextCache *cache;
    Text *t;
    Margin t_margin;
    Border t_border;
    Padding t_padding;
    //
    unsigned time;
    //
    unsigned spacing_time;
    unsigned spacing_deltaTime;
    const unsigned spacing_valMax = 50;
    const unsigned spacing_timeDelay = 16;
    char spacing_str[100] = "";
    //
    double fps;
    unsigned fps_time;
    unsigned fps_deltaTime;
    const unsigned fps_timeDelay = 100;
    char fps_str[20] = "FPS: 60";

    graphical_init();
    //
    w = SDL_CreateWindow(
        "3nd test of Text struct",
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
    //
    cache = TextCache_Create(r, fpath, ptsize);
    t = Text_Create(cache);
    t_margin = *Text_margin(t);
    t_border = *Text_border(t);
    t_padding = *Text_padding(t);
    //
    time = spacing_time = fps_time = SDL_GetTicks();
    
    //
    t_margin.color = (SDL_Color){255, 0, 0, 255};
    t_border.color = (SDL_Color){0, 255, 0, 255};
    t_padding.color = (SDL_Color){0, 0, 255, 255};
    bitmask = (MARGIN_TOP | MARGIN_RIGHT | MARGIN_BOTTOM | MARGIN_LEFT | BORDER_TOP | BORDER_RIGHT | BORDER_BOTTOM | BORDER_LEFT);

    while(1){
        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        SDL_RenderClear(r);
        //
        spacing_deltaTime = SDL_GetTicks() - spacing_time;
        fps_deltaTime = SDL_GetTicks() - fps_time;
        // printf("%i\n", bitmask);

        // fps
        if(fps_deltaTime >= fps_timeDelay){
            /*
            printf(
                "(%i %i %i %i)\n", 
                t_padding.bottom,
                t_padding.top,
                t_padding.right,
                t_padding.left
            );
            // */
            sprintf(fps_str, "FPS: %.2lf", fps);
        }

        // bitmask
        // printf("%i %i\n", bitmask, t_padding->bottom);
        if(bitmask & PADDING_BOTTOM && spacing_deltaTime >= spacing_timeDelay){
            ++t_padding.bottom;
        }
        if(bitmask & PADDING_TOP && spacing_deltaTime >= spacing_timeDelay){
            ++t_padding.top;
        }
        if(bitmask & PADDING_RIGHT && spacing_deltaTime >= spacing_timeDelay){
            ++t_padding.right;
        }
        if(bitmask & PADDING_LEFT && spacing_deltaTime >= spacing_timeDelay){
            ++t_padding.left;
        }

        //*
        if(bitmask & BORDER_BOTTOM && spacing_deltaTime >= spacing_timeDelay){
            ++t_border.bottom;
        }
        if(bitmask & BORDER_TOP && spacing_deltaTime >= spacing_timeDelay){
            ++t_border.top;
        }
        if(bitmask & BORDER_RIGHT && spacing_deltaTime >= spacing_timeDelay){
            ++t_border.right;
        }
        if(bitmask & BORDER_LEFT && spacing_deltaTime >= spacing_timeDelay){
            ++t_border.left;
        }

        if(bitmask & MARGIN_BOTTOM && spacing_deltaTime >= spacing_timeDelay){
            ++t_margin.bottom;
        }
        if(bitmask & MARGIN_TOP && spacing_deltaTime >= spacing_timeDelay){
            ++t_margin.top;
        }
        if(bitmask & MARGIN_RIGHT && spacing_deltaTime >= spacing_timeDelay){
            ++t_margin.right;
        }
        if(bitmask & MARGIN_LEFT && spacing_deltaTime >= spacing_timeDelay){
            ++t_margin.left;
        }
        // */

        // Draw fps
        Text_DrawUTF8(
            t,
            fps_str,
            TextConfig_Create(
                .scale_width = 1 / 2.0,
                .scale_height = 1 / 2.0,
                .wrap = 0,
                .color = (SDL_Color){255, 255, 255, 255},
                .y = 0,
                .x = 734,

                .margin = (Margin){},
                .border = (Border){},
                .padding = (Padding){},
            ),
            NULL
        );

        //* Draw text
        Text_DrawUTF8(
            t,
            str,
            TextConfig_Create(
                .scale_width = 1 / 2.0,
                .scale_height = 1 / 2.0,
                .wrap = 434,
                .color = (SDL_Color){255, 255, 0, 255},
                .x = 0,
                .y = 0,

                .padding = t_padding,
                .border = t_border,
                .margin = t_margin
            ),
            NULL
        );
        // */

        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    SDL_DestroyWindow(w);
                    SDL_DestroyRenderer(r);
                    SDL_Quit();
                    //
                    Text_Destroy(&t);
                    TextCache_Destroy(&cache);
                    //
                    exit(0);

                default:
                    break;
            }
        }

        SDL_RenderPresent(r);
        SDL_Delay(16);
        //
        if(spacing_deltaTime >= spacing_timeDelay){
            spacing_time = SDL_GetTicks();
        }
        if(fps_deltaTime >= fps_timeDelay){
            fps_time = SDL_GetTicks();
        }

        if(
            t_padding.bottom >= spacing_valMax
            || t_padding.top >= spacing_valMax
            || t_padding.right >= spacing_valMax
            || t_padding.left >= spacing_valMax

            || t_border.bottom >= spacing_valMax
            || t_border.top >= spacing_valMax
            || t_border.right >= spacing_valMax
            || t_border.left >= spacing_valMax

            || t_margin.bottom >= spacing_valMax
            || t_margin.top >= spacing_valMax
            || t_margin.right >= spacing_valMax
            || t_margin.left >= spacing_valMax
          ){
            t_padding.bottom =
                t_padding.top =
                t_padding.right = 
                t_padding.left = 
                //
                t_border.bottom =
                t_border.top =
                t_border.right = 
                t_border.left = 
                //
                t_margin.bottom =
                t_margin.top =
                t_margin.right = 
                t_margin.left = 0;

            ++bitmask;
        }

        fps = 1000.0 / (SDL_GetTicks() - time);
        time = SDL_GetTicks();
        bitmask %= (MARGIN_LEFT << 1);
        if(bitmask == 0){
            bitmask = 1;
        }
    }
}

#endif
