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
// #include"main.h"
#include<graphical.h>

#define VA_NUM_ARGS_IMPL(_0, _1, _2, _3, N, ...) N
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__,, 3, 2, 1, 0)

int main()
{
    /*
     * Please, run one test per program...
     */
    // 
    // Test SDL
    //
    // SimpleWindow();

    //
    // Test TextFAG struct
    //
    // TextFAG_Test();

    //
    // Text TextFA struct
    //
    // TextCache_Test("./assets/fonts/Ubuntu/Ubuntu-Regular.ttf", 50);

    //
    // Test Text struct
    //
    /*
    Text_Test1(
        "./assets/fonts/Ubuntu/Ubuntu-Regular.ttf",
        50,
        // "Lorem ipsum dolor sit amet, consectetur adipiscing elit. In mollis faucibus porttitor. Mauris tempor ut lorem ac laoreet. Quisque facilisis aliquet mauris a blandit. Sed magna ante, faucibus sit amet purus ac, eleifend posuere nunc.\nDuis id elit vulputate, sollicitudin odio nec, volutpat massa. Praesent auctor tincidunt massa, vitae interdum felis euismod sed. Vivamus ultrices, odio ac ullamcorper tincidunt, est urna iaculis lorem, a venenatis nunc magna ac quam. Donec nunc turpis, bibendum a lobortis at, auctor vitae augue."
         "#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
        );
    // */
    //*
    Text_Test2(
        "./assets/fonts/Ubuntu/Ubuntu-Regular.ttf",
        50,
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. In mollis faucibus porttitor. Mauris tempor ut lorem ac laoreet."
        // "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        // "Protocolo-Caramelo"
        // "Lorem ipsum dolor sit amet, consectetur adipiscing elit. In mollis faucibus porttitor. Mauris tempor ut lorem ac laoreet. Quisque facilisis aliquet mauris a blandit. Sed magna ante, faucibus sit amet purus ac, eleifend posuere nunc.\nDuis id elit vulputate, sollicitudin odio nec, volutpat massa. Praesent auctor tincidunt massa, vitae interdum felis euismod sed. Vivamus ultrices, odio ac ullamcorper tincidunt, est urna iaculis lorem, a venenatis nunc magna ac quam. Donec nunc turpis, bibendum a lobortis at, auctor vitae augue."
    );
    // */

    return 0;
}

#endif
