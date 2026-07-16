#include"main.h"

Ball balls[BALLS_AMT];
size_t balls_idx;
size_t balls_size = BALLS_AMT;
size_t balls_ptr;
size_t simulation_i;

//
void Balls_init()
{
    *Balls_ptr() = 0;
    while(*Balls_ptr() < *Balls_idx()){
        memset(Balls_getCurr(), 0, sizeof(*Balls_getCurr()));
        ++*Balls_ptr();
    }
}

void Balls_exit()
{
    *Balls_ptr() = 0;
    while(*Balls_ptr() < *Balls_idx()){
        Ball_exit(Balls_getCurr());
        ++*Balls_ptr();
    }
}

void Balls_render()
{
    simulation_i = 0;
    Balls_calculate_friction();
    for(simulation_i=0; simulation_i < SIMULATION_ITR_MAX; ++simulation_i){
        Balls_calculate_colision();
        Balls_calculate_friction();
        Balls_calculate_position();
    }

    // Check for colosition and calculate the vx and vy for all balls
    *Balls_ptr() = 0;
    while(*Balls_ptr() < *Balls_idx()){
        Ball_render(Balls_getCurr());
        ++*Balls_ptr();
    }

}

void Balls_event(SDL_Event e)
{
    switch(e.type){
        case SDL_KEYDOWN:
            Balls_event_keyDown(e);
            break;

        case SDL_KEYUP:
            Balls_event_keyUp(e);
            break;

        case SDL_MOUSEBUTTONDOWN:
            Balls_event_mouseButtonDown(e);
            break;

        case SDL_MOUSEBUTTONUP:
            Balls_event_mouseButtonUp(e);
            break;

        default:
            break;
    }

    *Balls_ptr() = 0;
    while(*Balls_ptr() < *Balls_idx()){
        Ball_event(Balls_getCurr(), e);
        ++*Balls_ptr();
    }
}

//
void Balls_calculate_friction()
{
    int win_w, win_h;
    int tex_w, tex_h;
    size_t i;
    Ball *b;
    T_TIMESTAMP timestamp_curr;

    // Check colisions with the screen wall
    *Balls_ptr() = 0;
    SDL_GetWindowSizeInPixels(
        *App_window(&app),
        &win_w,
        &win_h
    );
    for(i=0; i < *Balls_idx(); ++i){
        *Balls_ptr() = i;
        b = Balls_getCurr();
        if(*Ball_state(b) != BALLSTATE_DROPPED){
            continue;
        }

        //
        SDL_QueryTexture(
            *Texture_raw(Ball_texture(b)),
            NULL,
            NULL,
            &tex_w,
            &tex_h
        );
        tex_h *= Ball_width(b) / tex_w;
        tex_w = Ball_width(b);
        timestamp_curr = SDL_GetTicks();

        // Add gavity!
        if((int)(win_h - *Ball_y(b) - tex_h) > 0 && *Ball_state(b) == BALLSTATE_DROPPED && !simulation_i){
            *Ball_vy(b) += G_FORCE * (timestamp_curr - *Ball_timestamp(b)) / 1000;
        }

        // Check if ball hit a wall and add friction to it
        if(
            // Hit the left wall
            *Ball_x(b) + *Ball_vx(b) < 0
            // Hit the right wall
            || *Ball_x(b) + *Ball_vx(b) + tex_w >= win_w
            ){
            *Ball_vx(b) = -*Ball_vx(b) * FRICTION_ELASTIC_VAL;
            *Ball_vy(b) *= (1.0f - FRICTION_VAL);
        }
        if(
            // Hit the upper wall
            *Ball_y(b) + *Ball_vy(b) < 0 
            // Hit the under wall
            || *Ball_y(b) + *Ball_vy(b) + tex_h >= win_h
          ){
            *Ball_vx(b) *= (1.0f - FRICTION_VAL);
            *Ball_vy(b) = -*Ball_vy(b) * FRICTION_ELASTIC_VAL;
        }

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

        *Ball_timestamp(b) = timestamp_curr;
    }
}

void Balls_calculate_colision()
{
    // Check for possible colisions
    Ball *b1, *b2;
    size_t i, j;
    double dist_balls;
    double vn_cos, vn_sin, vn_v;
    double impulseX, impulseY, impulse;
    T_COL dist_x, vn_vx;
    T_ROW dist_y, vn_vy;

    for(i=0; i < *Balls_idx(); ++i){
        *Balls_ptr() = i;
        b1 = Balls_getCurr();
        for(j=0; j < *Balls_idx(); ++j){
            *Balls_ptr() = j;
            b2 = Balls_getCurr();
            if(*Ball_state(b1) != BALLSTATE_DROPPED){
                break;
            }
            if(j == i || *Ball_state(b2) != BALLSTATE_DROPPED){
                continue;
            }

            dist_x = *Ball_x(b1) - *Ball_x(b2) + *Ball_radius(b1) - *Ball_radius(b2) + *Ball_vx(b1) - *Ball_vx(b2);
            dist_y = *Ball_y(b1) - *Ball_y(b2) + *Ball_radius(b1) - *Ball_radius(b2) + *Ball_vy(b1) - *Ball_vy(b2);
            dist_balls = pow(pow(dist_x, 2) + pow(dist_y, 2), 0.5);
            if(*Ball_radius(b2) + *Ball_radius(b1) < dist_balls){
                continue;
            }

            vn_cos = dist_x / dist_balls;
            vn_sin = dist_y / dist_balls;
            vn_vx = *Ball_vx(b1) - *Ball_vx(b2);
            vn_vy = *Ball_vy(b1) - *Ball_vy(b2);
            vn_v = vn_vx * vn_cos + vn_vy * vn_sin;

            impulse = -(1.0 + COLISION_ELASTIC_VAL) * vn_v;
            impulse /= (1.0 / *Ball_weight(b1)) + (1.0 / *Ball_weight(b2));
            impulseX = impulse * vn_cos;
            impulseY = impulse * vn_sin;

            *Ball_vx(b1) += impulseX / *Ball_weight(b1);
            *Ball_vy(b1) += impulseY / *Ball_weight(b1);
            *Ball_vx(b2) -= impulseX / *Ball_weight(b2);
            *Ball_vy(b2) -= impulseY / *Ball_weight(b2);
        }
    }
}

void Balls_calculate_position()
{
    // Resolve the ball's positions
    Ball *b1, *b2;
    size_t i, j;
    double pen;
    double dist_x, dist_y, dist_balls;
    double vn_sin, vn_cos;
    T_WEIGHT massInv_b1, massInv_b2, massInv_tot;
    double corr_x, corr_y;

    for(i=0; i < *Balls_idx(); ++i){
        *Balls_ptr() = i;
        b1 = Balls_getCurr();
        for(j=0; j < *Balls_idx(); ++j){
            *Balls_ptr() = j;
            b2 = Balls_getCurr();
            if(j == i || *Ball_state(b2) != BALLSTATE_DROPPED)
                continue;

            dist_x = *Ball_x(b1) - *Ball_x(b2) + *Ball_radius(b1) - *Ball_radius(b2); // + *Ball_vx(b1) - *Ball_vx(b2);
            dist_y = *Ball_y(b1) - *Ball_y(b2) + *Ball_radius(b1) - *Ball_radius(b2); // + *Ball_vy(b1) - *Ball_vy(b2);
            dist_balls = pow(pow(dist_x, 2) + pow(dist_y, 2), 0.5);
            pen = *Ball_radius(b1) + *Ball_radius(b2) - dist_balls;
            // printf("Ball %li: %.2lf\n", i, dist_balls);
            // printf("Ball %li: %lf, %lf\n", i, *Ball_y(b1), *Ball_y(b2) + *Ball_radius(b2));
            if(pen < 0.0f){
                continue;
            }

            //
            vn_cos = dist_x / dist_balls;
            vn_sin = dist_y / dist_balls;
            massInv_b1 =
                (*Ball_state(b1) == BALLSTATE_DROPPED)? (1.0 / *Ball_weight(b1)) / 1000: 0;
            massInv_b2 = 
                (*Ball_state(b2) == BALLSTATE_DROPPED)? (1.0 / *Ball_weight(b2)) / 1000: 0;
            massInv_tot = massInv_b1 + massInv_b2;

            corr_x = vn_cos * pen / massInv_tot;
            corr_y = vn_sin * pen / massInv_tot;

            printf("Ball %li: %lf, %lf\n", i, corr_y * massInv_b1, corr_y * massInv_b2);

            *Ball_x(b1) += corr_x * massInv_b1;
            *Ball_y(b1) += corr_y * massInv_b1;
            *Ball_x(b2) -= corr_x * massInv_b2;
            *Ball_y(b2) -= corr_y * massInv_b2;
        }
    }
}

//
void Balls_event_keyDown(SDL_Event e)
{
    if(e.key.repeat)
        return;

    switch(e.key.keysym.sym){
        case SDLK_1:
            Balls_changeType(FOOTBALL_TYPE);
            break;

        case SDLK_2:
            Balls_changeType(BASKETBALL_TYPE);
            break;

        case SDLK_3:
            Balls_changeType(TENNIS_TYPE);
            break;

        case SDLK_4:
            Balls_changeType(PINGPONG_TYPE);
            break;

        default:
            break;
    }
}

void Balls_event_keyUp(SDL_Event e)
{
    if(e.key.repeat)
        return;
}

void Balls_event_mouseButtonDown(SDL_Event e)
{
    if(e.button.button == 2)
        return;
    Ball new_b = {
        .type = Balls_getCurrType(),
        .state = BALLSTATE_AIM,
        .x = e.button.x - Balls_getCurrType()->radius,
        .y = e.button.y - Balls_getCurrType()->radius
    };
    Ball_init(&new_b);

    Balls_add(new_b);
}

void Balls_event_mouseButtonUp(SDL_Event e)
{
    if(e.button.button == 2)
        return;
}
