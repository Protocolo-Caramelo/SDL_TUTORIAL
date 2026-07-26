#if defined(COMPILATION_NORMAL)
#include"main.h"

int main()
{
    SDL_Event e;

    graphical_init();
    App_init(&app);
    Guideline_init(&guideline);
    Balls_init();
    Infos_init();
    while(1){
        App_render(&app);
        Balls_render();
        Guideline_render(&guideline);
        Infos_render();

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

int main()
{
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
    int text_w, text_h;
    for(i=1; i < 100; ++i){
        *Text_fontWrap(&t) = i;
        SDL_Surface *s = TTF_RenderUTF8_Blended_Wrapped(
            *Text_font(&t), *Text_raw(&t), (SDL_Color){0, 0, 0, 255}, *Text_fontWrap(&t)
            );
        if(!s){
            printf("Error while creating text's surface: %s\n", SDL_GetError());
            exit(1);
        }
        Text_measureFont(&t, &text_w, &text_h);

        /*
        printf("Surface dimensions: %i %i\n", s->w, s->h);

        //
        printf("Text dimensions: %i %i\n", text_w, text_h);
        // */
        if(s->w != text_w && s->h != text_h){
            printf("Diff %i: %i %i VS %i %i\n", i, s->w, s->h, text_w, text_h);
        }
        SDL_FreeSurface(s);
    }

    return 0;
}

#endif
