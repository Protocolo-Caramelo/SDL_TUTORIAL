#ifndef GUIDELINE_H
#define GUIDELINE_H

#include"commons.h"
#include<stdbool.h>

typedef struct Guideline Guideline;
typedef struct GuidelineVTable GuidelineVTable;

extern Guideline guideline;

/*
 * GuidelineVTable struct
 */
struct GuidelineVTable {
    void (*init)(Guideline*);
    void (*exit)(Guideline*);
    void (*render)(Guideline*);
    void (*event)(Guideline*, SDL_Event);
};

#define GUIDELINE_INIT_PIXELFORMAT SDL_PIXELFORMAT_RGBA8888
#define GUIDELINE_INIT_TEXTUREACCESS SDL_TEXTUREACCESS_TARGET
void GuidelineVTable_init(Guideline*);
void GuidelineVTable_exit(Guideline*);

#define GUIDELINE_DASHEDLINE_WIDTH 10
#define GUIDELINE_DASHEDLINE_HEIGHT 5
#define GUIDELINE_DASHEDLINE_SPACE 15
#define GUIDELINE_DASHEDLINE_DIST_MOUSE 30
void GuidelineVTable_render(Guideline*);

#define GUIDELINE_MOUSEDOWN_INVALID_TIME 0
void GuidelineVTable_event(Guideline*, SDL_Event);


/*
 * Guideline struct
 */
struct Guideline {
    GuidelineVTable vtable;

    Texture t;
    T_COL init_x, mouse_x;
    T_ROW init_y, mouse_y;
    bool  mouse_pressed;
};

static inline Texture* Guideline_texture(Guideline*g)
{
    return &g->t;
}

static inline T_COL* Guideline_initX(Guideline*g)
{
    return &g->init_x;
}

static inline T_ROW* Guideline_initY(Guideline*g)
{
    return &g->init_y;
}

static inline T_COL* Guideline_mouseX(Guideline*g)
{
    return &g->mouse_x;
}

static inline T_ROW* Guideline_mouseY(Guideline*g)
{
    return &g->mouse_y;
}

static inline bool* Guideline_mouseButtonPressed(Guideline*g)
{
    return &g->mouse_pressed;
}

// Distance and angle calculations
static inline double Guideline_distX(Guideline*g)
{
    return *Guideline_mouseX(g) - *Guideline_initX(g);
}

static inline double Guideline_distY(Guideline*g)
{
    return *Guideline_mouseY(g) - *Guideline_initY(g);
}

static inline double Guideline_dist(Guideline*g)
{
    return pow(pow(Guideline_distX(g), 2) + pow(Guideline_distY(g), 2), 0.5);
}

static inline double Guideline_sin(Guideline*g)
{
    return Guideline_distY(g) / Guideline_dist(g);
}

static inline double Guideline_cos(Guideline*g)
{
    return Guideline_distX(g) / Guideline_dist(g);
}

double Guideline_angle(Guideline*g);

/*
 * Guideline methods
 */
static inline void Guideline_init(Guideline*g)
{
    g->vtable.init(g);
}

static inline void Guideline_exit(Guideline*g)
{
    g->vtable.exit(g);
}

static inline void Guideline_render(Guideline*g)
{
    g->vtable.render(g);
}

static inline void Guideline_event(Guideline*g, SDL_Event e)
{
    g->vtable.event(g, e);
}

/*
 * Guideline events functions
 */
void Guideline_event_mouseButtonDown(Guideline*g, SDL_Event e);
void Guideline_event_mouseButtonUp(Guideline*g, SDL_Event e);
void Guideline_event_mouseMotion(Guideline*g, SDL_Event e);

#endif
