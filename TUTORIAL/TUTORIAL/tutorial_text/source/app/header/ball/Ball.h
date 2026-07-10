#ifndef BALL_H
#define BALL_H

#include"commons.h"

typedef struct Ball Ball;
typedef struct BallVTable BallVTable;

#define G_FORCE 9.8

/*
 * BallVTable struct
 */
struct BallVTable {
    TextureVTable texture_vtable;

    void (*init)(Ball*);
    void (*exit)(Ball*);
    void (*render)(Ball*);
    void (*event)(Ball*, SDL_Event);
};

/*
 * Ball struct
 */
struct Ball {
    BallVTable *vtable;
    Texture texture;
    T_COL x, vx;
    T_ROW y, vy;

    double radius;
};

// getters / setters
static inline BallVTable** Ball_vtable(Ball*b)
{
    return &b->vtable;
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
    return &b->radius;
}

// properties that isn't attributes
static inline double Ball_v(Ball*b)
{
    return pow(pow(*Ball_x(b), 2) + pow(*Ball_y(b), 2), 0.5);
}

static inline double Ball_sin(Ball*b)
{
    return *Ball_vx(b) / Ball_v(b);
}

static inline double Ball_cos(Ball*b)
{
    return *Ball_vy(b) / Ball_v(b);
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
static inline void Ball_textureInit(Ball*b)
{
    b->vtable->texture_vtable.init(Ball_texture(b));
}

static inline void Ball_textureExit(Ball*b)
{
    b->vtable->texture_vtable.exit(Ball_texture(b));
}

static inline void Ball_init(Ball*b)
{
    b->vtable->init(b);
}

static inline void Ball_exit(Ball*b)
{
    b->vtable->exit(b);
}

static inline void Ball_render(Ball*b)
{
    b->vtable->render(b);
}

static inline void Ball_event(Ball*b, SDL_Event e)
{
    b->vtable->event(b, e);
}

#endif
