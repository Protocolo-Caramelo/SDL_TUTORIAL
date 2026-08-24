#ifndef GTEXTURE_H
#define GTEXTURE_H

#include"GCommons.h"
#include<SDL2/SDL_render.h>
#include<SDL2/SDL_events.h>

typedef struct Texture Texture;

/*
 * Texture struct
 */
struct Texture {
    // TextureVTable vtable;
    SDL_Texture *raw;
    SDL_Renderer *renderer;
};
// WRAP_FIELD(Texture, vtable, TextureVTable);
WRAP_FIELD(Texture, raw, SDL_Texture*);
WRAP_FIELD(Texture, renderer, SDL_Renderer*);

//
// Methods
//
/* Methods for set later */
void Texture_Init(Texture*t, void(*func)(Texture*));
void Texture_Exit(Texture*t, void(*func)(Texture*));
void Texture_Render(Texture*t, void(*func)(Texture*));
void Texture_Event(Texture*t, void(*func)(Texture*, SDL_Event));

void Texture_Clear(Texture*t);

#endif
