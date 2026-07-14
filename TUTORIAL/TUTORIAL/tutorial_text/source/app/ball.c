#include"main.h"

BallVTable ball_vtable = {
    .init = &BallVTable_init,
    .exit = &BallVTable_exit,
    .render = &BallVTable_render,
    .event = &BallVTable_event
};

BallType BT_Football = {
    .radius = FOOTBALL_RADIUS,
    .tex_path = FOOTBALL_TEXTURE_PATH,
    .vtable = &ball_vtable,
    .weight = FOOTBALL_WEIGHT,
};
BallType BT_Basketball = {
    .radius = BASKETBALL_RADIUS,
    .tex_path = BASKETBALL_TEXTURE_PATH,
    .vtable = &ball_vtable,
    .weight = BASKETBALL_WEIGHT,
};
BallType BT_Tennis = {
    .radius = TENNIS_RADIUS,
    .tex_path = TENNIS_TEXTURE_PATH,
    .vtable = &ball_vtable,
    .weight = TENNIS_WEIGHT,
};
BallType BT_PingPong = {
    .radius = PINGPONG_RADIUS,
    .tex_path = PINGPONG_TEXTURE_PATH,
    .vtable = &ball_vtable,
    .weight = PINGPONG_WEIGHT
};

//
void BallVTable_init(Ball*b)
{
    Texture *t;
    t = Ball_texture(b);

    *Texture_renderer(t) = *App_renderer(&app);
    *Texture_raw(t) = IMG_LoadTexture(
        *Texture_renderer(t),
        *Ball_texture_path(b)
        );

    if(!*Texture_raw(t)){
        printf("Error while initializing ball: %s\n", SDL_GetError());
        exit(1);
    }
}

void BallVTable_exit(Ball*b)
{
    Texture *t;
    t = Ball_texture(b);

    SDL_DestroyTexture(*Texture_raw(t));
}

void BallVTable_render(Ball*b)
{
    int tex_w, win_w;
    int tex_h, win_h;

    SDL_GetWindowSizeInPixels(
        *App_window(&app),
        &win_w,
        &win_h
    );
    SDL_QueryTexture(
        *Texture_raw(Ball_texture(b)),
        NULL,
        NULL,
        &tex_w,
        &tex_h
    );
    tex_h = Ball_width(b) / tex_w * tex_h;
    tex_w = Ball_width(b);

    // Increase velocity
    *Ball_x(b) += *Ball_vx(b);
    *Ball_y(b) += *Ball_vy(b);

    if(*Ball_x(b) + tex_w > win_w){
        *Ball_x(b) = win_w - tex_w;
    }
    else if(*Ball_x(b) < 0){
        *Ball_x(b) = 0;
    }
    if(*Ball_y(b) + tex_h > win_h){
        *Ball_y(b) = win_h - tex_h;
    }
    else if(*Ball_y(b) < 0){
        *Ball_y(b) = 0;
    }

    //
    Texture *t;
    SDL_Rect dest;

    t = Ball_texture(b);
    dest.x = *Ball_x(b);
    dest.y = *Ball_y(b);
    dest.w = tex_w;
    dest.h = tex_h;
    if(*Ball_state(b) == BALLSTATE_DROPPED){
        SDL_SetTextureColorMod(*Texture_raw(t), 255, 255, 255);
        SDL_SetTextureAlphaMod(*Texture_raw(t), 255);
    }
    if(*Ball_state(b) == BALLSTATE_AIM){
        SDL_SetTextureColorMod(*Texture_raw(t), 150, 150, 150);
        SDL_SetTextureAlphaMod(*Texture_raw(t), 192);
    }

    // printf("%i %i\n", dest.w, dest.h);
    SDL_RenderCopy(
        *Texture_renderer(t),
        *Texture_raw(t),
        NULL,
        &dest
    );

}

void BallVTable_event(Ball*b, SDL_Event e)
{
    switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            Ball_event_mouseButtonDown(b, e);
            break;

        case SDL_MOUSEBUTTONUP:
            Ball_event_mouseButtonUp(b, e);
            break;
        default:
            break;
    }
}

//
void Ball_event_mouseButtonDown(Ball*b, SDL_Event e)
{
    if(e.button.button == 2)
        return;
    // printf("Mouse button down\n");
}

void Ball_event_mouseButtonUp(Ball*b, SDL_Event e)
{
    if(e.button.button == 2)
        return;

    double dist;
    dist = Guideline_dist(&guideline);
    if(*Ball_state(b) == BALLSTATE_AIM && dist > 0){
        *Ball_vx(b) = dist * -Guideline_cos(&guideline) / 10;
        *Ball_vy(b) = dist * -Guideline_sin(&guideline) / 10;
    }
    else if(*Ball_state(b) == BALLSTATE_AIM && !dist){
        *Ball_vx(b) = 0;
        *Ball_vy(b) = -1;
    }
    *Ball_state(b) = BALLSTATE_DROPPED;
    *Ball_timestamp(b) = SDL_GetTicks();
    // printf("%.2lf, %.2lf\n", *Ball_vx(b), *Ball_vy(b));
}
