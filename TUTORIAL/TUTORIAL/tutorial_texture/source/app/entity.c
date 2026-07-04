#include"app.h"

Entity entity;

//
T_COL* Entity_x(const Entity*e)
{
    return Texture_x(Entity_texture(e));
}

T_ROW* Entity_y(const Entity*e)
{
    return Texture_y(Entity_texture(e));
}

T_COL* Entity_vx(const Entity*e)
{
    return &e->vx;
}

T_ROW* Entity_vy(const Entity*e)
{
    return &e->vy;
}

T_COL* Entity_width(const Entity*e)
{
    return &e->width;
}

T_ROW* Entity_height(const Entity*e)
{
    return &e->height;
}

Texture* Entity_texture(const Entity*e)
{
    return &e->texture;
}


// 
void Entity_initialize()
{
    memset(&entity, 0, sizeof(entity));

    T_COL *x, *vx, *w;
    T_ROW *y, *vy, *h;
    Texture *t;
    SDL_Renderer **t_r;

    x = Entity_x(&entity);
    y = Entity_y(&entity);
    vx = Entity_vx(&entity);
    vy = Entity_vy(&entity);
    w = Entity_width(&entity);
    h = Entity_height(&entity);
    t = Entity_texture(&entity);
    t_r = Texture_renderer(t);

    *x = ENTITY_INIT_X;
    *y = ENTITY_INIT_Y;
    *vx = ENTITY_INIT_VX;
    *vy = ENTITY_INIT_VY;
    *w = ENTITY_INIT_WIDTH;
    *h = ENTITY_INIT_HEIGHT;
    *t_r = *Window_renderer(&app);
    Texture_loadFromIMG(t, "./assets/TextureSample.png");
}

void Entity_events()
{
    T_COL *vx, *x, ew;
    T_ROW *vy, *y, eh;
    // App window size
    int w, h;

    vx = Entity_vx(&entity);
    vy = Entity_vy(&entity);
    ew = *Entity_width(&entity);
    eh = *Entity_height(&entity);
    x = Entity_x(&entity);
    y = Entity_y(&entity);
    SDL_GL_GetDrawableSize(
        *Window_raw(&app),
        &w, &h
    );

    if(*x + *vx + ew >= w || *x + *vx < 0){
        *vx = -*vx;
    }
    if(*y + *vy + eh >= h || *y + *vy < 0){
        *vy = -*vy;
    }

    *x += *vx;
    *y += *vy;
}

void Entity_render()
{
    SDL_Rect dest;
    SDL_Texture *t;

    dest.x = *Entity_x(&entity);
    dest.y = *Entity_y(&entity);
    t = *Texture_raw(Entity_texture(&entity));
    SDL_QueryTexture(t, NULL, NULL, &dest.w, &dest.h);

    dest.w = *Entity_width(&entity);
    dest.h = *Entity_height(&entity);

    SDL_RenderCopy(
        *Texture_renderer(&entity.texture),
        t, NULL, &dest
    );
}
