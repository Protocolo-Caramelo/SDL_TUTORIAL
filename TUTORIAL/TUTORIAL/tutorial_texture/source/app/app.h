#ifndef APP_H
#define APP_H

#include<GInit.h>
#include<GWindow.h>
#include<GTexture.h>
#include<time.h>

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

T_COL* Entity_x(const Entity*);
T_ROW* Entity_y(const Entity*);
T_COL* Entity_vx(const Entity*);
T_ROW* Entity_vy(const Entity*);
T_COL* Entity_width(const Entity*);
T_ROW* Entity_height(const Entity*);
Texture* Entity_texture(const Entity*);


#define ENTITY_INIT_WIDTH 100
#define ENTITY_INIT_HEIGHT 100
#define ENTITY_INIT_X (rand() % (APP_INIT_WIDTH - ENTITY_INIT_WIDTH - 10))
#define ENTITY_INIT_Y (rand() % (APP_INIT_HEIGHT - ENTITY_INIT_HEIGHT - 10))
#define ENTITY_INIT_VX (rand() % 3)
#define ENTITY_INIT_VY (rand() % 3)
extern Entity entity;

void Entity_initialize();
void Entity_events();
void Entity_render();

void doApp();

#endif
