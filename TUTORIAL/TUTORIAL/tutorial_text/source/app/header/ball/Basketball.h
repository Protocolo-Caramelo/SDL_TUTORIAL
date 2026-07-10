#ifndef BASKETBALL_H
#define BASKETBALL_H

#include"ball/Ball.h"

#define BASKETBALL_AMT 10

typedef BallVTable BasketballVTable;
typedef Ball Basketball;

extern BasketballVTable basketballs_vtable;
extern Basketball basketballs[];

// BastballVTable functions
#define BASKETBALL_INIT_TEXTURE_PATH "./assets/basketball.png"
void BasketballVTable_textureInit(Texture*);
void BasketballVTable_textureExit(Texture*);

void BasketballVTable_init(Basketball*);
void BasketballVTable_exit(Basketball*);
void BasketballVTable_render(Basketball*);
void BasketballVTable_event(Basketball*, SDL_Event);

// Basketball events
void Basketball_event_mouseButtonDown(Basketball*, SDL_Event);
void Basketball_event_mouseButtonUp(Basketball*, SDL_Event);

#endif
