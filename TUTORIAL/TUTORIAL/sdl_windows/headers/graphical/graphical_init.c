#include<graphical_init.h>

bool graphical_video_initialized = 0;

void graphical_setup()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       printf("Error while initializing SDL: %s\n", SDL_GetError());
       exit(1);
       return;
    }

    graphical_video_initialized = 1;
}
