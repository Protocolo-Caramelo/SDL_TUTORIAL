#include"main.h"

TextVTable InfosVTable = {
    .init = &InfosVTable_init,
    .exit = &InfosVTable_exit,
    .render = &InfosVTable_render,
    .event = &InfosVTable_event,
};
TTF_Font* InfoFont;

// Infos
Text info_fps = {
    .vtable = &InfosVTable,
};
Text info_ballsCount = {
    .vtable = &InfosVTable,
};
uint64_t info_balls = (INFO_BALL_ID | INFO_BALL_PX | INFO_BALL_PY);

// Others vars
T_TIMESTAMP time_fps;
double fps;
uint16_t fps_itr;


//
// Virtual methods
//
void InfosVTable_init(Text*t)
{
    *Text_renderer(t) = *App_renderer(&app);
    *Text_fontSize(t) = 1;
    *Text_font(t) = InfoFont;
    *Text_paddingRaw(t) = INFOS_PADDING;
    *Text_borderRaw(t) = INFOS_BORDER;
    *Text_marginRaw(t) = INFOS_MARGIN;
}

void InfosVTable_exit(Text*t)
{
    free(*Text_raw(t));
}

void InfosVTable_render(Text*t)
{
    if(!*Text_raw(t)){
        return;
    }

    Texture t_margin;
    int margin_w, margin_h;
    int margin_x, margin_y;

    Texture t_border;
    int border_w, border_h;
    int border_x, border_y;

    Texture t_padding;
    int padding_w, padding_h;
    int padding_x, padding_y;

    Texture t_font;
    int font_w, font_h;
    int font_x, font_y;

    //
    /*
    *t_margin = Text_textureMargin(t);
    Text_measureMargin(t, &margin_w, &margin_h);
    Text_positionMargin(t, &margin_x, &margin_y);

    *t_border = Text_textureBorder(t);
    Text_measureBorder(t, &border_w, &border_h);
    Text_positionBorder(t, &border_x, &border_y);
    // */

    // printf("|%s|: %i %i, %i %i\n", *Text_raw(t), font_w, font_h, font_x, font_y);

    // Render Border


    // Render padding
    // /*
    t_padding = Text_texturePadding(t);
    Text_measurePadding(t, &padding_w, &padding_h);
    Text_positionPadding(t, &padding_x, &padding_y);

    SDL_Rect padding_dest = {
        .x = padding_x,
        .y = padding_y,
        .w = padding_w,
        .h = padding_h
    };
    SDL_RenderCopy(
        *Text_renderer(t),
        *Texture_raw(&t_padding),
        NULL,
        &padding_dest
    );

    // Render Text
    t_font = Text_textureFont(t);
    Text_measureFont(t, &font_w, &font_h);
    Text_positionFont(t, &font_x, &font_y);

    SDL_Rect font_dest = {
        .x = font_x,
        .y = font_y,
        .w = font_w,
        .h = font_h,
    };
    SDL_RenderCopy(
        *Text_renderer(t),
        *Texture_raw(&t_font),
        NULL,
        &font_dest
    );

    // 
    SDL_Color c = *Text_paddingColor(t);
    // printf("%s: %i %i %i %i\n", *Text_raw(t), c.r, c.g, c.b, c.a);

    SDL_DestroyTexture(*Texture_raw(&t_font));
    SDL_DestroyTexture(*Texture_raw(&t_padding));
}

void InfosVTable_event(Text*t, SDL_Event e)
{
}

// Functions for general use
void Infos_init()
{
    InfoFont = TTF_OpenFont(INFOS_FONT_PATH, INFOS_FONT_SIZE);
    if(!InfoFont){
        printf("Error while initializng info text: %s\n", SDL_GetError());
        exit(1);
    }

    Text_init(&info_fps);
    Text_init(&info_ballsCount);

    //
    time_fps = 0;
    fps = fps_itr = 0;
    *Text_raw(&info_fps) = malloc(sizeof(char) * INFO_FPS_MEM_SIZE);
    *Text_renderer(&info_fps) = *App_renderer(&app);
    *Text_x(&info_fps) = INFO_FPS_X;
    *Text_y(&info_fps) = INFO_FPS_Y;
    *Text_fontColor(&info_fps) = INFO_FPS_FONTCOLOR;
    *Text_fontSize(&info_fps) = INFO_FPS_FONTSIZE;
    *Text_fontWrap(&info_fps) = INFO_FPS_FONTWRAP;

    *Text_raw(&info_ballsCount) = malloc(sizeof(char) * INFO_BALLSCOUNT_MEM_SIZE);
    *Text_fontColor(&info_ballsCount) = INFO_BALLSCOUNT_FONTCOLOR;
    *Text_fontSize(&info_ballsCount) = INFO_BALLSCOUNT_FONTSIZE;
    *Text_fontWrap(&info_ballsCount) = INFO_BALLSCOUNT_FONTWRAP;
    *Text_renderer(&info_ballsCount) = *App_renderer(&app);

    size_t i;
    Text *bInfos;
    for(i=0; i < BALLS_AMT; ++i){
        bInfos = Ball_infos(Balls_get(i));
        *Text_vtable(bInfos) = &InfosVTable;
        Text_init(bInfos);

        *Text_raw(bInfos) = malloc(sizeof(char) * INFO_BALL_MEM_SIZE);
        *Text_fontColor(bInfos) = INFO_BALL_FONTCOLOR;
        *Text_fontSize(bInfos) = INFO_BALL_FONTSIZE;
        *Text_fontWrap(bInfos) = INFO_BALL_FONTWRAP;
        *Text_renderer(bInfos) = *App_renderer(&app);
    }
}

void Infos_exit()
{
    Text_exit(&info_fps);
    Text_exit(&info_ballsCount);
    size_t i;
    for(i=0; i < *Balls_idx(); ++i){
        Text_exit(Ball_infos(Balls_get(i)));
    }
}

void Infos_render()
{
    if(INFO_FPS == ON){
        Infos_render_infoFPS();
    }

    if(INFO_BALLSCOUNT == ON){
        Infos_render_infoBallsCount();
    }

    if(INFO_BALL == ON){
        // Infos_render_infoBall();
    }
}

void Infos_event(SDL_Event e)
{
}

// Update functions
void Infos_render_infoFPS()
{
    if(fps_itr >= FPS_ITR_MAX){
        fps_itr = 0;
        fps = 0;
    }
    ++fps_itr;
    fps += 1000.0 / (SDL_GetTicks() - time_fps);

    sprintf(*Text_raw(&info_fps), "FPS: %.0lf", fps / fps_itr);
    time_fps = SDL_GetTicks();
    Text_render(&info_fps);
}

void Infos_render_infoBallsCount()
{
    int margin_w, margin_h;
    int margin_x, margin_y;

    Text_measureMargin(&info_fps, &margin_w, &margin_h);
    Text_positionMargin(&info_fps, &margin_x, &margin_y);

    *Text_x(&info_ballsCount) = margin_x;
    *Text_y(&info_ballsCount) = margin_y + margin_h;

    sprintf(*Text_raw(&info_ballsCount), "Balls count: %li / %i", *Balls_idx(), BALLS_AMT);
    Text_render(&info_ballsCount);
}

void Infos_render_infoBall()
{
    int win_w, win_h;
    size_t i;
    Ball *b;
    Text *info;
    char **info_str;
    int info_marginW, info_marginH;

    SDL_GetWindowSizeInPixels(
        *App_window(&app), 
        &win_w,
        &win_h
    );

    for(i=0; i < *Balls_idx(); ++i){
        b = Balls_get(i);
        info = Ball_infos(b);
        info_str = Text_raw(info);
        *info_str[0] = '\0';

        if(info_balls & INFO_BALL_ID){
            sprintf(*info_str, "%sId: %li\n", *info_str, *Balls_ptr() + 1);
        }
        if(info_balls & INFO_BALL_MS){
            sprintf(*info_str, "%sMass: %.2lf\n", *info_str, *Ball_weight(b));
        }
        if(info_balls & INFO_BALL_RD){
            sprintf(*info_str, "%sRadius: %.2lf\n", *info_str, *Ball_radius(b));
        }
        if(info_balls & INFO_BALL_PX){
            sprintf(*info_str, "%sX: %.2lf\n", *info_str, *Ball_x(b));
        }
        if(info_balls & INFO_BALL_PY){
            sprintf(*info_str, "%sY: %.2lf\n", *info_str, *Ball_y(b));
        }
        if(info_balls & INFO_BALL_VX){
            sprintf(*info_str, "%sVx: %.2lf\n", *info_str, *Ball_vx(b));
        }
        if(info_balls & INFO_BALL_VY){
            sprintf(*info_str, "%sVy: %.2lf\n", *info_str, *Ball_vy(b));
        }
        if(info_balls & INFO_BALL_ST){
            sprintf(*info_str, "%sSin: %.2lf\n", *info_str, Ball_sin(b));
        }
        if(info_balls & INFO_BALL_CS){
            sprintf(*info_str, "%sCos: %.2lf\n", *info_str, Ball_cos(b));
        }
        if(info_balls & INFO_BALL_TN){
            sprintf(*info_str, "%sTan: %.2lf\n", *info_str, Ball_tan(b));
        }
        if(info_balls & INFO_BALL_AR){
            sprintf(*info_str, "%sAngle(rad): %.2lf\n", *info_str, Ball_angleRad(b));
        }
        if(info_balls & INFO_BALL_AD){
            sprintf(*info_str, "%sAngle(deg): %.2lf\n", *info_str, Ball_angleDeg(b));
        }

        // printf("%s\n", *info_str);
        Text_measureMargin(info, &info_marginW, &info_marginH);
        *Text_x(Ball_infos(b)) = 
            (*Ball_x(b) + Ball_width(b) + info_marginW <= win_w)? *Ball_x(b) + Ball_width(b):
            *Ball_x(b) - info_marginW / 2;
        *Text_y(Ball_infos(b)) = 
            (*Ball_y(b) + info_marginH <= win_h)? *Ball_y(b):
            *Ball_y(b) - info_marginH;

        Text_render(info);
    }
}
