#if defined(COMPILATION_NORMAL)
#include"main.h"

int main()
{
    SDL_Event e;

    graphical_init();
    App_init(&app);
    Guideline_init(&guideline);
    Balls_init();
    // Infos_init();
    while(1){
        App_render(&app);
        Balls_render();
        Guideline_render(&guideline);
        // Infos_render();

        while(SDL_PollEvent(&e)){
            App_event(&app, e);
            Balls_event(e);
            Guideline_event(&guideline, e);
        }

        App_present(&app);
        SDL_Delay(DELAY_PER_FRAME);
        // printf("%lf\n", 1000.0 / (SDL_GetTicks() - t));
    }
    return 0;
}

#elif defined(COMPILATION_DEVQUOTE)
#include"main.h"
#include<stdio.h>

#define VA_NUM_ARGS_IMPL(_0, _1, _2, _3, N, ...) N
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__,, 3, 2, 1, 0)

int main()
{
    /*
    graphical_init();

    Text t;
    *Text_raw(&t) = malloc(sizeof(char) * 100);
    *Text_font(&t) = TTF_OpenFont(
        INFOS_FONT_PATH,
        INFOS_FONT_SIZE
    );
    *Text_fontSize(&t) = 1; // / 2.0;
    if(!*Text_font(&t)){
        printf("Error while initializing text's font: %s\n", SDL_GetError());
        exit(1);
    }

    // strcpy(*Text_raw(&t), "Id:1\nX: 24.00\n Y: 350.00\n");
    strcpy(*Text_raw(&t), "AAAAAAAAAAAAabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    // strcpy(*Text_raw(&t), "AAAAAAAAAAAA");
    int i;
    int tot, errors;
    int text_w, text_h;

    errors = tot = 0;
    for(i=0; i < 100; ++i){
        *Text_fontWrap(&t) = i;
        SDL_Surface *s = TTF_RenderUTF8_Blended_Wrapped(
            *Text_font(&t), *Text_raw(&t), (SDL_Color){0, 0, 0, 255}, *Text_fontWrap(&t)
            );
        if(!s){
            printf("Error while creating text's surface: %s\n", SDL_GetError());
            exit(1);
        }
        Text_measureFont(&t, &text_w, &text_h);

        if(s->w != text_w || s->h != text_h){
            printf("Diff %i: %i %i VS %i %i\n", i, s->w, s->h, text_w, text_h);
            ++errors;
        }
        SDL_FreeSurface(s);

        ++tot;
    }
    printf("Accuracy: %.2lf\n", 1 - errors / (double)tot);
    // */
    graphical_init();

    SDL_Window *w;
    SDL_Renderer *r;
    SDL_Event e;
    SDL_Rect dest;
    TextFont test;

    w = SDL_CreateWindow(
        "Tutorial text",
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
    *TextFont_renderer(&test) = r;
    TextFont_load(&test, "assets/fonts/Ubuntu/Ubuntu-Regular.ttf");
    memset(&dest, 0, sizeof(dest));
    SDL_QueryTexture(*Texture_raw(TextFont_texture(&test)),  NULL, NULL, &dest.w, &dest.h);

    while(1){
        SDL_SetRenderDrawColor(r, 0, 255, 255, 255);
        SDL_RenderClear(r);
        SDL_RenderCopy(
            r,
            *Texture_raw(TextFont_texture(&test)),
            NULL,
            &dest
        );

        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    SDL_DestroyWindow(w);
                    SDL_DestroyRenderer(r);
                    TextFont_destroy(&test);
                    SDL_Quit();
                    exit(1);
                    break;
                    
                default:
                    break;
            }
        }

        SDL_RenderPresent(r);
        SDL_Delay(16);
    }

    return 0;
}

#endif
