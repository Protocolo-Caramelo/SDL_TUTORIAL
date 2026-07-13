#ifndef APP_H
#define APP_H

#include"commons.h"

typedef Window App;
typedef WindowVTable AppVTable;

extern const AppVTable app_vtable;
extern App app;

/*
 * AppVTable methods
 */
void AppVTable_init(App*);
void AppVTable_exit(App*);
void AppVTable_render(App*);
void AppVTable_present(App*);
void AppVTable_event(App*, SDL_Event);

/*
 * App methods
 */
static inline SDL_Window** App_window(App*app)
{
    return Window_raw(app);
}

static inline SDL_Renderer** App_renderer(App*app)
{
    return Window_renderer(app);
}


static inline void App_init(App*app)
{
    app->vtable.init(app);
}

static inline void App_exit(App*app)
{
    app->vtable.exit(app);
}

static inline void App_render(App*app)
{
    app->vtable.render(app);
}

static inline void App_present(App*app)
{
    app->vtable.present(app);
}

static inline void App_event(App*app, SDL_Event e)
{
    app->vtable.event(app, e);
}

#endif
