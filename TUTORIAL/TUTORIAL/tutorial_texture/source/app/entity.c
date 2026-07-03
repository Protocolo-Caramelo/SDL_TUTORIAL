#include"app.h"

Entity entity;

void Entity_initialize()
{
    memset(&entity, 0, sizeof(entity));

    Texture_x_def(&entity.texture, ENTITY_INIT_X);
    Texture_y_def(&entity.texture, ENTITY_INIT_Y);
    Texture_renderer_def(
        &entity.texture,
        Window_renderer(&app)
    );
    Texture_loadFromIMG(&entity.texture, "./assets/TextureSample.png");

    entity.vx = ENTITY_INIT_VX;
    entity.vy = ENTITY_INIT_VY;
    entity.width = ENTITY_WIDTH;
    entity.height = ENTITY_HEIGHT;
}

void Entity_events()
{
    T_COL *vx, x, ew;
    T_ROW *vy, y, eh;
    // App window size
    int w, h;

    vx = &entity.vx;
    vy = &entity.vy;
    ew = entity.width;
    eh = entity.height;
    x = Texture_x(&entity.texture);
    y = Texture_y(&entity.texture);
    SDL_GL_GetDrawableSize(
        Window_raw(&app),
        &w, &h
    );

    if(x + *vx + ew >= w || x + *vx < 0){
        *vx = -*vx;
    }
    if(y + *vy + eh >= h || y + *vy < 0){
        *vy = -*vy;
    }

    x += *vx;
    y += *vy;
    printf("%i %i\n", *vx, x);

    Texture_x_def(&entity.texture, x);
    Texture_y_def(&entity.texture, y);
}

void Entity_render()
{
    SDL_Rect dest;
    SDL_Texture *t;

    dest.x = Texture_x(&entity.texture);
    dest.y = Texture_y(&entity.texture);
    t = Texture_raw(&entity.texture);
    SDL_QueryTexture(t, NULL, NULL, &dest.w, &dest.h);

    dest.w = ENTITY_WIDTH;
    dest.h = ENTITY_HEIGHT;

    SDL_RenderCopy(
        Texture_renderer(&entity.texture),
        t, NULL, &dest
    );
}
