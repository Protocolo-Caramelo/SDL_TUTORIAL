#include"main.h"

Ball balls[BALLS_AMT];
size_t balls_idx;
size_t balls_size = BALLS_AMT;
size_t balls_ptr;

//
void Balls_init()
{
    *Balls_ptr() = 0;
    while(*Balls_ptr() < *Balls_idx()){
        memset(Balls_getCurr(), 0, sizeof(*Balls_getCurr()));
        ++*Balls_ptr();
    }
}

void Balls_exit()
{
    *Balls_ptr() = 0;
    while(*Balls_ptr() < *Balls_idx()){
        Ball_exit(Balls_getCurr());
        ++*Balls_ptr();
    }
}

void Balls_render()
{
    // Balls_printTypeName();
    *Balls_ptr() = 0;
    while(*Balls_ptr() < *Balls_idx()){
        Ball_render(Balls_getCurr());
        ++*Balls_ptr();
    }
}

void Balls_event(SDL_Event e)
{
    switch(e.type){
        case SDL_KEYDOWN:
            Balls_event_keyDown(e);
            break;

        case SDL_KEYUP:
            Balls_event_keyUp(e);
            break;

        case SDL_MOUSEBUTTONDOWN:
            Balls_event_mouseButtonDown(e);
            break;

        case SDL_MOUSEBUTTONUP:
            Balls_event_mouseButtonUp(e);
            break;

        default:
            break;
    }

    *Balls_ptr() = 0;
    while(*Balls_ptr() < *Balls_idx()){
        Ball_event(Balls_getCurr(), e);
        ++*Balls_ptr();
    }
}

void Balls_event_keyDown(SDL_Event e)
{
    if(e.key.repeat)
        return;

    switch(e.key.keysym.sym){
        case SDLK_1:
            Balls_changeType(FOOTBALL_TYPE);
            break;

        case SDLK_2:
            Balls_changeType(BASKETBALL_TYPE);
            break;

        case SDLK_3:
            Balls_changeType(TENNIS_TYPE);
            break;

        case SDLK_4:
            Balls_changeType(PINGPONG_TYPE);
            break;

        default:
            break;
    }
}

void Balls_event_keyUp(SDL_Event e)
{
    if(e.key.repeat)
        return;
}

void Balls_event_mouseButtonDown(SDL_Event e)
{
    if(e.button.button == 2)
        return;
    Ball new_b = {
        .type = Balls_getCurrType(),
        .state = BALLSTATE_AIM,
        .x = e.button.x - Balls_getCurrType()->radius,
        .y = e.button.y - Balls_getCurrType()->radius
    };
    Ball_init(&new_b);

    Balls_add(new_b);
}

void Balls_event_mouseButtonUp(SDL_Event e)
{
    if(e.button.button == 2)
        return;
}
