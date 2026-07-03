#include<GTexture.h>

void Texture_x_def(Texture*t, T_COL x)
{
    t->x = x;
}

void Texture_y_def(Texture*t, T_ROW y)
{
    t->y = y;
}

void Texture_renderer_def(Texture*t, SDL_Renderer*r)
{
    t->renderer = r;
}

void Texture_raw_def(Texture*t, SDL_Texture*tex)
{
    t->texture = tex;
}


T_COL Texture_x(const Texture*t)
{
    return t->x;
}

T_ROW Texture_y(const Texture*t)
{
    return t->y;
}

SDL_Renderer* Texture_renderer(const Texture*t)
{
    return t->renderer;
}

SDL_Texture* Texture_raw(const Texture*t)
{
    return t->texture;
}


void Texture_loadFromIMG(Texture*to, const char*path)
{
    to->texture = IMG_LoadTexture(Texture_renderer(to), path);
    if(!to->texture){
        printf("Error into loading texture: %s\n", SDL_GetError());
        exit(1);
    }
}
