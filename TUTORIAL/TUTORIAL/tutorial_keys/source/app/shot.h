#ifndef ENTITY_H
#define ENTITY_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<graphical.h>

typedef int16_t T_COL;
typedef int16_t T_ROW;
typedef double T_ANGLE;
typedef struct Shot Shot;
typedef struct ShotVTable ShotVTable;

/*
 * Shot Method Virtual Table struct
 */
struct ShotVTable{
    void (*init)(Shot*, Window*);
    void (*exit)(Shot*);
    void (*render)(Shot*);
    void (*present)(Shot*);

    void (*event)(Shot*, SDL_Event);
};

/*
 * Shot struct
 */
struct Shot{
    Texture t;
    T_COL x, vx, width;
    T_ROW y, vy, height;

    T_ANGLE angle;

    ShotVTable vtable;
};

static inline Texture* Shot_texture(Shot*s)
{
    return &s->t;
}

static inline T_COL* Shot_x(Shot*s)
{
    return &s->x;
}

static inline T_ROW* Shot_y(Shot*s)
{
    return &s->y;
}

static inline T_COL* Shot_vx(Shot*s)
{
    return &s->vx;
}

static inline T_ROW* Shot_vy(Shot*s)
{
    return &s->vy;
}

static inline T_COL* Shot_width(Shot*s)
{
    return &s->width;
}

static inline T_ROW* Shot_height(Shot*s)
{
    return &s->height;
}

static inline T_ANGLE* Shot_angle(Shot*s)
{
    return &s->angle;
}

static inline ShotVTable* Shot_vtable(Shot*s)
{
    return &s->vtable;
}

// Access methods
static inline void Shot_init(Shot*s, Window*w)
{
    s->vtable.init(s, w);
}

static inline void Shot_exit(Shot*s)
{
    s->vtable.exit(s);
}

static inline void Shot_render(Shot*s)
{
    s->vtable.render(s);
}

static inline void Shot_present(Shot*s)
{
    s->vtable.present(s);
}

static inline void Shot_event(Shot*s, SDL_Event e)
{
    s->vtable.event(s, e);
}

#endif
