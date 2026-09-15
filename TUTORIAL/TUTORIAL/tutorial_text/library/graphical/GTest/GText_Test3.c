#ifdef COMPILATION_DEVQUOTE
#include"GTest.h"

void Text_Test3(char*fpath, unsigned ptsize, char*str)
{
    SDL_Window *w;
    SDL_Renderer *r;
    SDL_Event e;
    //
    TextCache *cache;
    Text *t;

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

    while(1){
        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        SDL_RenderClear(r);

        Text_DrawUTF8(
            t,
            str,
            TextConfig_Create(
                .scale_width = 1 / 2.0,
                .scale_height = 1 / 2.0,
                .wrap = 1024,
                .color = (SDL_Color){255, 255, 0, 255},
                .x = 0,
                .y = 0,
                //
                .margin.top = 10,
                .margin.bottom = 70,
                .margin.right = 10,
                .margin.left = 10,
                .margin.color = (SDL_Color){255, 0, 0, 125},
            ),
            NULL
        );

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
    }
}

#endif
