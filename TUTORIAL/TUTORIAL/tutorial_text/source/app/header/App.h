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
#define APP_INIT_WINDOW_NAME "Tutorial text"
#define APP_INIT_WINDOW_XPOS SDL_WINDOWPOS_UNDEFINED
#define APP_INIT_WINDOW_YPOS SDL_WINDOWPOS_UNDEFINED
#define APP_INIT_WINDOW_WIDTH 900
#define APP_INIT_WINDOW_HEIGHT 450
#define APP_INIT_WINDOW_FLAGS (SDL_WINDOW_RESIZABLE)
#define APP_INIT_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED)
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
