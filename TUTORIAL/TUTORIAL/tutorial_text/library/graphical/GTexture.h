#ifndef GTEXTURE_H
#define GTEXTURE_H

#include"GCommuns.h"

typedef struct TextureVTable TextureVTable;
typedef struct Texture Texture;

/*
 * TextureVTable struct
 */
struct TextureVTable {
    void (*init)(Texture*);
    void (*exit)(Texture*);

    void (*event)(Texture*);
};

/*
 * Texture struct
 */
struct Texture {
    TextureVTable vtable;
    SDL_Texture *raw;
    SDL_Renderer *renderer;
};

static inline TextureVTable* Texture_vtable(Texture*t)
{
    return &t->vtable;
}

static inline SDL_Texture** Texture_raw(Texture*t)
{
    return &t->raw;
}

static inline SDL_Renderer** Texture_renderer(Texture*t)
{
    return &t->renderer;
}


static inline void Texture_init(Texture*t)
{
    t->vtable.init(t);
}

static inline void Texture_exit(Texture*t)
{
    t->vtable.exit(t);
}


#endif
