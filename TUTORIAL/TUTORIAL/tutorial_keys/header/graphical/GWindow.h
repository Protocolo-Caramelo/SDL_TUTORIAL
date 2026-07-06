#ifndef GWINDOW_H
#define GWINDOW_H

#include<SDL2/SDL.h>
#include<string.h>

typedef struct Window Window;
typedef struct WindowVTable WindowVTable;

/*
 * Window Method Virtual Table struct
 */
struct WindowVTable{
    void (*init)(Window*);
    void (*exit)(Window*);
    void (*render)(Window*);
    void (*present)(Window*);

    void (*event)(Window*, SDL_Event);
};

/*
 * Window struct
 */
struct Window{
    SDL_Renderer *renderer;
    SDL_Window *raw;

    WindowVTable vtable;
};

static inline SDL_Renderer **Window_renderer(Window*w)
{
    return &w->renderer;
}
static inline SDL_Window **Window_raw(Window*w)
{
    return &w->raw;
}
static inline WindowVTable *Window_vtable(Window*w)
{
    return &w->vtable;
}

// Access methods
static inline void Window_init(Window*w)
{
    w->vtable.init(w);
}
static inline void Window_exit(Window*w)
{
    w->vtable.exit(w);
}
static inline void Window_render(Window*w)
{
    w->vtable.render(w);
}
static inline void Window_present(Window*w)
{
    w->vtable.present(w);
}

static inline void Window_event(Window*w, SDL_Event e)
{
    w->vtable.event(w, e);
}

#endif
