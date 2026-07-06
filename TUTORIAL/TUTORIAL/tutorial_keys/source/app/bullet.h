#ifndef BULLET_H
#define BULLET_H

#include"app.h"
#include"shot.h"
#include<math.h>
#define RAD_TO_DEG(rad) (rad * 180 / M_PI)
#define DEG_TO_RAD(deg) (deg * M_PI / 180)

typedef Shot Bullet;
typedef ShotVTable BulletVTable;
extern const BulletVTable bullet_vtable;
extern Bullet bullet;

//
#define BULLET_INIT_IMG_PATH "./assets/Bullet.png"
#define BULLET_INIT_X (APP_INIT_WIDTH / 2)
#define BULLET_INIT_Y (APP_INIT_HEIGHT / 2)
#define BULLET_INIT_VX 0
#define BULLET_INIT_VY 0
#define BULLET_INIT_WIDTH 100
#define BULLET_INIT_HEIGHT 61
#define BULLET_INIT_ANGLE 0

void Bullet_init(Bullet*, Window*to);
void Bullet_exit(Bullet*);

#define BULLET_ROTATE_DURATION 100 // 0.1 seconds
#define BULLET_ROTATE_SPEED 180
void Bullet_render(Bullet*);
void Bullet_present(Bullet*);

void Bullet_event(Bullet*, SDL_Event);

// Events for bullet
void Bullet_KeyDown(Bullet*, SDL_Scancode);
void Bullet_KeyUp(Bullet*, SDL_Scancode);

#endif
