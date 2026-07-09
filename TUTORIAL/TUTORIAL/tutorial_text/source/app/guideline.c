#include"main.h"

double Guideline_angle(Guideline*g)
{
    double angle;
    if((angle = atan2(-Guideline_sin(g), Guideline_cos(g))) < 0){
        angle += 2 * M_PI;
    }


    return angle;
}

//
const GuidelineVTable guideline_vtable = {
    .init = &GuidelineVTable_init,
    .exit = &GuidelineVTable_exit,
    .render = &GuidelineVTable_render,
    .event = &GuidelineVTable_event
};

Guideline guideline = {
    .vtable = guideline_vtable
};


void GuidelineVTable_init(Guideline*g)
{
    Texture *t;
    t = Guideline_texture(g);

    *Texture_renderer(t) = *App_renderer(&app);
    *Texture_raw(t) = SDL_CreateTexture(
        *Texture_renderer(t),
        GUIDELINE_INIT_PIXELFORMAT,
        GUIDELINE_INIT_TEXTUREACCESS,
        1,
        1
    );
    *Guideline_mouseButtonPressed(g) = 0;
}

void GuidelineVTable_exit(Guideline*g)
{
    SDL_DestroyTexture(*Texture_raw(Guideline_texture(g)));
}

void GuidelineVTable_render(Guideline*g)
{
    if(!*Guideline_mouseButtonPressed(g)){
        return;
    }

    // Create a texture for line from init mouse position to current mouse position
    Texture *t;
    SDL_Texture* target_prev;
    t = Guideline_texture(g);
    target_prev = SDL_GetRenderTarget(*Texture_renderer(t));

    SDL_DestroyTexture(*Texture_raw(t));
    *Texture_raw(t) = SDL_CreateTexture(
        *Texture_renderer(t),
        GUIDELINE_INIT_PIXELFORMAT,
        GUIDELINE_INIT_TEXTUREACCESS,
        GUIDELINE_DASHEDLINE_WIDTH,
        GUIDELINE_DASHEDLINE_HEIGHT
    );
    if(!*Texture_raw(t)){
        printf("Error while create guideline texture: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetRenderTarget(*Texture_renderer(t), *Texture_raw(t));
    SDL_SetRenderDrawColor(
        *Texture_renderer(t),
        255,
        255,
        255,
        255
    );
    SDL_RenderClear(*Texture_renderer(t));
    SDL_SetRenderTarget(*Texture_renderer(t), target_prev);

    // Render the line 
    double init_x, x;
    double init_y, y;
    double dist, angle;

    init_x = x = *Guideline_initX(g);
    init_y = y = *Guideline_initY(g);
    do {
        SDL_Rect dest = {
            .x = x,
            .y = y - GUIDELINE_DASHEDLINE_HEIGHT / 2,
            .w = GUIDELINE_DASHEDLINE_WIDTH,
            .h = GUIDELINE_DASHEDLINE_HEIGHT
        };
        SDL_Point center = {
            .x = dest.w / 2,
            .y = dest.h / 2
        };
        /*
        if((angle = (RAD_TO_DEG(Guideline_angle(g)) + 90)) >= 360){
            angle -= 360;
        }
        // */
        angle = RAD_TO_DEG(Guideline_angle(g));

        SDL_RenderCopyEx(
            *Texture_renderer(t),
            *Texture_raw(t),
            NULL,
            &dest,
            -angle,
            &center,
            SDL_FLIP_NONE
        );


        // printf("%.2lf\n", angle);
        x += GUIDELINE_DASHEDLINE_SPACE * Guideline_cos(g);
        y += GUIDELINE_DASHEDLINE_SPACE * Guideline_sin(g);
        dist = pow(pow(x - init_x, 2) + pow(y - init_y, 2), 0.5);
    } while(dist <= Guideline_dist(g));
}

void GuidelineVTable_event(Guideline*g, SDL_Event e)
{
    switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            Guideline_event_mouseButtonDown(g, e);
            break;

        case SDL_MOUSEBUTTONUP:
            Guideline_event_mouseButtonUp(g, e);
            break;

        case SDL_MOUSEMOTION:
            Guideline_event_mouseMotion(g, e);
            break;

        default:
            break;
    }
}

/*
 * Guideline events functions
 */
void Guideline_event_mouseButtonDown(Guideline*g, SDL_Event e)
{
    if(e.button.button == 2){
        return;
    }

    *Guideline_mouseButtonPressed(g) = 1;
    *Guideline_initX(g) = *Guideline_mouseX(g) = e.button.x;
    *Guideline_initY(g) = *Guideline_mouseY(g) = e.button.y;
}

void Guideline_event_mouseButtonUp(Guideline*g, SDL_Event e)
{
    *Guideline_mouseButtonPressed(g) = 0;
    *Guideline_initX(g) = *Guideline_mouseX(g) = 0;
    *Guideline_initY(g) = *Guideline_mouseY(g) = 0;
}

void Guideline_event_mouseMotion(Guideline*g, SDL_Event e)
{
    if(!*Guideline_mouseButtonPressed(g))
        return;

    *Guideline_mouseX(g) = e.button.x;
    *Guideline_mouseY(g) = e.button.y;
    // printf("%.2lf\n", RAD_TO_DEG(Guideline_angle(g)));
}
