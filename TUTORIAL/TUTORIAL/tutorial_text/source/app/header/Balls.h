#ifndef BALLS_H
#define BALLS_H

#include"ball/Ball.h"

extern Ball balls[];
extern size_t balls_idx;
extern size_t balls_size;
extern size_t balls_ptr;
extern size_t simulation_i;

typedef enum {
    FOOTBALL_TYPE,
    BASKETBALL_TYPE,
    TENNIS_TYPE,
    PINGPONG_TYPE
} BallType_id;
static BallType *balls_types[] = {
    [FOOTBALL_TYPE] = &BT_Football,
    [BASKETBALL_TYPE] = &BT_Basketball,
    [TENNIS_TYPE] = &BT_Tennis,
    [PINGPONG_TYPE] = &BT_PingPong
};
static BallType_id balls_selectedType;

static inline size_t* Balls_size()
{
    return &balls_size;
}

static inline size_t* Balls_idx()
{
    return &balls_idx;
}

static inline size_t* Balls_ptr()
{
    return &balls_ptr;
}

static inline Ball* Balls_getCurr()
{
    return &balls[*Balls_ptr()];
}

static inline void Balls_next()
{
    *Balls_ptr() = (!*Balls_ptr())? 0: (*Balls_ptr() + 1) % *Balls_size();
}

static inline void Balls_prev()
{
    *Balls_ptr() = (!*Balls_ptr())? *Balls_size() - 1: *Balls_ptr() - 1;
}

static inline bool Balls_add(const Ball b)
{
    if(*Balls_idx() >= *Balls_size()){
        return false;
    }

    balls[(*Balls_idx())++] = b;
    return true;
}

static inline void Balls_changeType(const BallType_id bt_id)
{
    balls_selectedType = bt_id;
}

static inline BallType* Balls_getCurrType()
{
    return balls_types[balls_selectedType];
}

static inline void Balls_printTypeName()
{
    switch(balls_selectedType){
        case FOOTBALL_TYPE:
            printf("Football\n");
            break;

        case BASKETBALL_TYPE:
            printf("Basketball\n");
            break;

        case TENNIS_TYPE:
            printf("Tennis\n");
            break;

        case PINGPONG_TYPE:
            printf("PingPong\n");
            break;

        default:
            break;
    }
}

/*
 * General functions for all balls
 */
void Balls_init();
void Balls_exit();
void Balls_render();
void Balls_event(SDL_Event);

void Balls_calculate_friction();
void Balls_calculate_colision();
void Balls_calculate_position();
void Balls_calculate_velocity();

void Balls_event_keyDown(SDL_Event);
void Balls_event_keyUp(SDL_Event);
void Balls_event_mouseButtonDown(SDL_Event);
void Balls_event_mouseButtonUp(SDL_Event);

#endif
