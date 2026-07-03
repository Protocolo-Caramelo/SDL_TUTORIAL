#ifndef APP_H
#define APP_H

#include<GInit.h>
#include<GWindow.h>
#include<GTexture.h>

#define APP_INIT_X SDL_WINDOWPOS_UNDEFINED
#define APP_INIT_Y SDL_WINDOWPOS_UNDEFINED
#define APP_INIT_WIDTH 900
#define APP_INIT_HEIGHT 500
#define APP_INIT_WINDOW_FLAGS SDL_WINDOW_RESIZABLE
#define APP_INIT_RENDERER_FLAGS SDL_RENDERER_ACCELERATED
extern Window app;

void App_initialize();
void App_destroy();
void App_events();
void App_render();

/* */
typedef struct {
    Texture texture;
    T_COL vx;
    T_ROW vy;

    T_COL width;
    T_ROW height;
} Entity;

#define ENTITY_WIDTH 100
#define ENTITY_HEIGHT 100
#define ENTITY_INIT_X 60
#define ENTITY_INIT_Y 60
#define ENTITY_INIT_VX 2
#define ENTITY_INIT_VY 1
extern Entity entity;

void Entity_initialize();
void Entity_events();
void Entity_render();

void doApp();

#endif
