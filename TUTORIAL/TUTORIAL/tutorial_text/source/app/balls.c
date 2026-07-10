#include"main.h"

void Balls_init()
{
    extern Basketball basketballs[];
    size_t i;

    // Basketballs
    for(i=0; i < BASKETBALL_AMT; ++i){
        basketballs[i].vtable = &basketballs_vtable;
        Ball_init(&basketballs[i]);
    }
}

void Balls_exit()
{
}

void Balls_render()
{
}

void Balls_event(SDL_Event e)
{
    extern Basketball basketballs[];
    size_t i;

    // Basketballs
    for(i=0; i < BASKETBALL_AMT; ++i){
        Ball_event(&basketballs[i], e);
    }
}
