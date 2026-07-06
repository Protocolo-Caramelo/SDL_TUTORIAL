#include"main.h"

const BulletVTable bullet_vtable = {
    .init = &Bullet_init,
    .exit = &Bullet_exit,
    .render = &Bullet_render,
    .present = &Bullet_present,
    .event = &Bullet_event
};

Bullet bullet = {
    .vtable = bullet_vtable
};

//
void Bullet_init(Bullet*b, Window*to)
{
    *Texture_renderer(Shot_texture(b)) = *Window_renderer(&app);
    Texture_loadFromImg(Shot_texture(b), BULLET_INIT_IMG_PATH);
    *Shot_x(b) = BULLET_INIT_X;
    *Shot_y(b) = BULLET_INIT_Y;
    *Shot_vx(b) = BULLET_INIT_VX;
    *Shot_vy(b) = BULLET_INIT_VY;
    *Shot_width(b) = BULLET_INIT_WIDTH;
    *Shot_height(b) = BULLET_INIT_HEIGHT;
    *Shot_angle(b) = BULLET_INIT_ANGLE;
}

void Bullet_exit(Bullet*b)
{
    SDL_DestroyTexture(*Texture_raw(Shot_texture(b)));
}

void Bullet_render(Bullet*b)
{
    // Check if bullet rearch the end of screen
    int w, h;
    SDL_GetWindowSizeInPixels(*Window_raw(&app), &w, &h);

    if(*Shot_x(b) <= 0 || (*Shot_x(b) + *Shot_width(b)) >= w){
        *Shot_vx(b) = -*Shot_vx(b);
    }
    if(*Shot_y(b) <= 0 || (*Shot_y(b) + *Shot_height(b)) >= h){
        *Shot_vy(b) = -*Shot_vy(b);
    }

    // Incress the position of bullet using it velocity
    *Shot_x(b) += *Shot_vx(b);
    *Shot_y(b) += *Shot_vy(b);

    // Calculate the bullet's angle
    double hipo, angle_x, angle_y, angle;
    hipo = sqrt(pow(*Shot_vx(b), 2) + pow(*Shot_vy(b), 2));
    angle_x = ((*Shot_vx(b)) / hipo);
    angle_y = ((*Shot_vy(b)) / hipo);
    if((angle = atan2(-angle_y, angle_x)) < 0){
        angle += 2 * M_PI;
    }
    
    angle = RAD_TO_DEG(angle);
    double angle_delta;
    if((angle_delta = angle - *Shot_angle(b) + 180) >= 360){
        angle_delta -= 360;
    }
    if(angle_delta < 0){
        angle_delta += 360;
    }
    angle_delta -= 180;

    // printf("%.2lf, %.2lf, %.2lf\n", angle_x, angle_y, angle);
    // printf("%.2lf %.2lf\n", angle, angle_delta);
    // printf("%.2lf, %.2lf, %.2lf\n", *Shot_angle(b), angle, angle_delta);
    // /*
    *Shot_angle(b) += 
        (angle_delta == angle_delta) ? angle_delta / (100 / 16):
        0;
    // */

    // Render the bullet
    SDL_Rect dest;
    Texture *t;

    dest.x = *Shot_x(b);
    dest.y = *Shot_y(b);
    t = Shot_texture(b);

    SDL_QueryTexture(*Texture_raw(t), NULL, NULL, &dest.w, &dest.h);
    dest.w = *Shot_width(b);
    dest.h = *Shot_height(b);
    SDL_Point center = {
        dest.w / 2,
        dest.h / 2
    };

    /*
    SDL_RenderCopy(
        *Texture_renderer(t),
        *Texture_raw(t),
        NULL,
        &dest
    );
    // */
    SDL_RenderCopyEx(
        *Texture_renderer(t),
        *Texture_raw(t),
        NULL,
        &dest,
        -*Shot_angle(b),
        &center,
        SDL_FLIP_HORIZONTAL
    );
}

void Bullet_present(Bullet*b)
{
}

void Bullet_event(Bullet*b, SDL_Event e)
{
    /*
    if(e.key.repeat){
        return;
    }
    // */
    switch(e.type){
        case SDL_KEYDOWN:
            Bullet_KeyDown(b, e.key.keysym.scancode);
            break;

        case SDL_KEYUP:
            // Bullet_KeyUp(b, e.key.keysym.scancode);
            break;

        default:
            break;
    }
}

//
void Bullet_KeyDown(Bullet*b, SDL_Scancode key)
{
    switch(key){
        case SDL_SCANCODE_UP:
            --(*Shot_vy(b));
            break;

        case SDL_SCANCODE_DOWN:
            ++(*Shot_vy(b));
            break;

        case SDL_SCANCODE_LEFT:
            --(*Shot_vx(b));
            break;

        case SDL_SCANCODE_RIGHT:
            ++(*Shot_vx(b));
            break;

        default:
            break;
    }
}

void Bullet_KeyUp(Bullet*b, SDL_Scancode key)
{
    switch(key){
        case SDL_SCANCODE_UP:
            --(*Shot_vy(b));
            break;

        case SDL_SCANCODE_DOWN:
            ++(*Shot_vy(b));
            break;

        case SDL_SCANCODE_LEFT:
            ++(*Shot_vx(b));
            break;

        case SDL_SCANCODE_RIGHT:
            --(*Shot_vx(b));
            break;

        default:
            break;
    }
}
