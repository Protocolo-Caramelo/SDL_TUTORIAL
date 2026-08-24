#include"GTexture.h"

void Texture_Clear(Texture*t)
{
    SDL_Texture *t_prev;
    t_prev = SDL_GetRenderTarget(*Texture_renderer(t));

    SDL_SetRenderTarget(*Texture_renderer(t), *Texture_raw(t));
    SDL_SetRenderDrawColor(*Texture_renderer(t), 255, 255, 255, 0);
    SDL_RenderClear(*Texture_renderer(t));

    SDL_SetRenderTarget(*Texture_renderer(t), t_prev);
}
