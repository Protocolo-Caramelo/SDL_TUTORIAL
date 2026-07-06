#include<GInit.h>

void graphical_init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error in sdl video initialization: %s\n", SDL_GetError());
        exit(1);
    }

    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)){
        printf("Error in initializtion of imgages types");
        exit(1);
    }
}
