#ifndef BALL_H
#define BALL_H

#include"commons.h"

typedef struct Ball Ball;
typedef struct BallVTable BallVTable;
typedef struct BallType BallType;

extern BallType BT_Football, BT_Basketball, BT_Tennis, BT_PingPong;

/*
 * BallVTable struct
 */
struct BallVTable {
    void (*init)(Ball*);
    void (*exit)(Ball*);
    void (*render)(Ball*);
    void (*event)(Ball*, SDL_Event);
};

void BallVTable_textureExit(Texture*);
void BallVTable_init(Ball*);
void BallVTable_exit(Ball*);
void BallVTable_render(Ball*);
void BallVTable_event(Ball*, SDL_Event);

/*
 * BallType struct
 */
struct BallType {
    double radius;
    char *tex_path;
    BallVTable *vtable;
    T_WEIGHT weight;
};

/*
 * Balls states
 */
typedef enum {
    BALLSTATE_AIM,
    BALLSTATE_DROPPED
} BallState;

/*
 * Ball struct
 */
struct Ball {
    BallType *type;
    BallState state;
    Texture texture;
    T_TIMESTAMP timestamp_last;
    T_COL x, vx;
    T_ROW y, vy;
};

// getters / setters
static inline BallType** Ball_type(Ball*b)
{
    return &b->type;
}

static inline BallState* Ball_state(Ball*b)
{
    return &b->state;
}

static inline BallVTable** Ball_vtable(Ball*b)
{
    return &((*Ball_type(b))->vtable);
}

static inline Texture* Ball_texture(Ball*b)
{
    return &b->texture;
}

static inline T_COL* Ball_x(Ball*b)
{
    return &b->x;
}

static inline T_ROW* Ball_y(Ball*b)
{
    return &b->y;
}

static inline T_COL* Ball_vx(Ball*b)
{
    return &b->vx;
}

static inline T_ROW* Ball_vy(Ball*b)
{
    return &b->vy;
}

static inline double* Ball_radius(Ball*b)
{
    return &((*Ball_type(b))->radius);
}

static inline char** Ball_texture_path(Ball*b)
{
    return &((*Ball_type(b))->tex_path);
}

static inline T_COL Ball_width(Ball*b)
{
    return (*Ball_type(b))->radius * 2;
}

static inline T_WEIGHT* Ball_weight(Ball*b)
{
    return &(*Ball_type(b))->weight;
}

// properties that isn't attributes
static inline double Ball_v(Ball*b)
{
    return pow(pow(*Ball_vx(b), 2) + pow(*Ball_vy(b), 2), 0.5);
}

static inline double Ball_sin(Ball*b)
{
    return *Ball_vy(b) / Ball_v(b);
}

static inline double Ball_cos(Ball*b)
{
    return *Ball_vx(b) / Ball_v(b);
}

static inline double Ball_tan(Ball*b)
{
    return Ball_sin(b) / Ball_cos(b);
}

static inline double Ball_angleRad(Ball*b)
{
    return (atan2(-Ball_sin(b), Ball_cos(b)) > 0)? atan2(-Ball_sin(b), Ball_cos(b)):
        atan2(-Ball_sin(b), Ball_cos(b)) + 2 * M_PI;
}

static inline double Ball_angleDeg(Ball*b)
{
    return RAD_TO_DEG(Ball_angleRad(b));
}

static inline bool Ball_initialized(Ball*b)
{
    return *Texture_raw(Ball_texture(b)) == NULL;
}

// methods
static inline void Ball_init(Ball*b)
{
    (*Ball_vtable(b))->init(b);
}

static inline void Ball_exit(Ball*b)
{
    (*Ball_vtable(b))->exit(b);
}

static inline void Ball_render(Ball*b)
{
    (*Ball_vtable(b))->render(b);
}

static inline void Ball_event(Ball*b, SDL_Event e)
{
    (*Ball_vtable(b))->event(b, e);
}

// Ball events
void Ball_event_mouseButtonDown(Ball*, SDL_Event);
void Ball_event_mouseButtonUp(Ball*, SDL_Event);

#endif
