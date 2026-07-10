#include"main.h"

BasketballVTable basketballs_vtable = {
    .texture_vtable = {
        .init = &BasketballVTable_textureInit,
        .exit = &BasketballVTable_textureExit
    },
    .init = &BasketballVTable_init,
    .exit = &BasketballVTable_exit,
    .render = &BasketballVTable_render,
    .event = &BasketballVTable_event
};

Basketball basketballs[BASKETBALL_AMT];

// Texture methods
void BasketballVTable_textureInit(Texture*t)
{
    *Texture_renderer(t) = *App_renderer(&app);
    *Texture_raw(t) = IMG_LoadTexture(
        *Texture_renderer(t),
        BASKETBALL_INIT_TEXTURE_PATH
    );
    if(!*Texture_raw){
        printf("Error while initializing basketball's texture: %s\n", SDL_GetError());
        exit(1);
    }
}

void BasketballVTable_textureExit(Texture*t)
{
    SDL_DestroyTexture(*Texture_raw(t));
    *Texture_renderer(t) = NULL;
}

// Basketball methods
void BasketballVTable_init(Basketball*b)
{
    *Texture_raw(Ball_texture(b)) = NULL;
    *Texture_renderer(Ball_texture(b)) = NULL;
}

void BasketballVTable_exit(Basketball*b)
{
    Ball_textureExit(b);
}

void BasketballVTable_render(Basketball*b)
{
    if(!*Texture_raw(Ball_texture(b))){
        return;
    }
}

void BasketballVTable_event(Basketball*b, SDL_Event e)
{
    switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            Basketball_event_mouseButtonDown(b, e);
            break;

        case SDL_MOUSEBUTTONUP:
            Basketball_event_mouseButtonUp(b, e);
            break;

        default:
            break;
    }
}

// Basketball events
void Basketball_event_mouseButtonDown(Basketball*b, SDL_Event e)
{
    printf("Basketball hold\n");
}

void Basketball_event_mouseButtonUp(Basketball*b, SDL_Event e)
{
    printf("Basketball hold off\n");
}
