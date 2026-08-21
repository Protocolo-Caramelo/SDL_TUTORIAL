#include"GInit.h"

void graphical_init()
{
    if(SDL_Init(SDL_INIT_VIDEO)){
        printf("Error while initializing sdl video: %s\n", SDL_GetError());
        exit(1);
    }

    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)){
        printf("Error while initializing images: %s\n", SDL_GetError());
        exit(1);
    }

    if(TTF_Init()){
        printf("Error while initializing ttf libary: %s\n", SDL_GetError());
        exit(1);
    }
}
