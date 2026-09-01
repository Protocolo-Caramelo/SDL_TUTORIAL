#include"GText.h"

//
// Properties
//
int Text_getUTF8(Text*t, size_t idx)
{
    if(idx > Text_GetSizeUTF8(t)){
        GRAPHICAL_LOG_CRITICAL("Can't access index %li from Text struct, which have %li size", idx, Text_GetSizeUTF8(t));
        return 0;
    }

    char *byte;
    size_t i;
    int c;

    byte = utf8codepoint(*Text_raw(t), &c);
    i = 0;
    while((i++) < idx && (byte = utf8codepoint(byte, &c)));
    return c;
}

size_t Text_GetSizeUTF8(Text*t)
{
    return utf8len(*Text_raw(t));
}


char* Text_GetUTF8(Text*t)
{
    return *Text_raw(t);
}

void Text_SetUTF8(Text*t, char*str)
{
    free(*Text_raw(t));
    *Text_raw(t) = malloc(sizeof(**Text_raw(t)) * utf8size(str));
    utf8cpy(*Text_raw(t), str);
}

//
// Measure
//
//*
void Text_MeasureUTF8(Text*t, int*texInitX, int*texInitY, int*w, int*h, void(*func)(Text*, TextChar*))
{
    size_t i;
    //
    int width, height;
    int lineskip;
    //
    Glyph *c_glyph;
    int c;
    int cIns_xMax, cIns_xMin;
    int cIns_yMax, cIns_yMin;
    TextChar cIns, cIns_prev;

    lineskip = *Text_lineskip(t) * *Text_scaleHeight(t);
    //
    cIns = (TextChar){};
    cIns.rotation = DEG_TO_RAD(*Text_chrRotation(t));
    cIns.rotation_cos = cos(cIns.rotation);
    cIns.rotation_sin = sin(cIns.rotation);
    cIns.x = 0;
    // cIns.y = *Text_lineskip(t) * *Text_scaleHeight(t);
    cIns.y = 0;

    cIns_xMax = cIns_xMin = cIns_yMax = cIns_yMin = 0;
    //
    i = 0;
    cIns_prev = cIns;
    while((c = Text_getUTF8(t, (i++))) != '\0'){
        // printf("Text_MeasureUTF8: %.2lf %.2lf\n", cIns.x, cIns.y);
        c_glyph = TextCache_GetGlyph(*Text_cache(t), c, *Text_chrFmt(t));

        cIns.c = c;
        cIns.idx = i - 1;
        if(func){
            func(t, &cIns);
        }
        if(cIns.rotation != cIns_prev.rotation){
            cIns.rotation_cos = cos(cIns.rotation);
            cIns.rotation_sin = sin(cIns.rotation);
        }
        cIns.width =
            (
            c_glyph->w * fabs(cIns.rotation_cos) * *Text_scaleWidth(t)
            + c_glyph->h * fabs(cIns.rotation_sin) * *Text_scaleHeight(t)
            );
        cIns.height = 
            (
            c_glyph->h * fabs(cIns.rotation_cos) * *Text_scaleHeight(t)
            + c_glyph->w * fabs(cIns.rotation_sin) * *Text_scaleWidth(t)
            );

        // *
        cIns.x += cIns.width + *Text_chrDist(t);
        if(
            c == '\n' ||
            (*Text_wrap(t) && cIns.x > *Text_wrap(t))
        ){
            cIns.y += lineskip;
            cIns.x = cIns.width;
        }

        if(cIns.x > cIns_xMax){
            cIns_xMax = cIns.x;
        }
        if(cIns.x < cIns_xMin){
            cIns_xMin = cIns.x - cIns.width * 3;
        }
        if(cIns.y > cIns_yMax){
            cIns_yMax = cIns.y;
        }
        if(cIns.y < cIns_yMin){
            cIns_yMin = cIns.y;
        }
    }
    width = abs(cIns_xMax) + abs(cIns_xMin);
    height = abs(cIns_yMax) + abs(cIns_yMin); // + *Text_lineskip(t) * *Text_scaleHeight(t);
    printf("Text_MeasureUTF8: (%i, %i) (%i %i)\n", cIns_xMax, cIns_xMin, cIns_yMax, cIns_yMin);
    // printf("Text_MeasureUTF8: %i %i\n", width, height);

    if(w){
        *w = (int)floor(width + 1);
    }
    if(h){
        *h = (int)floor(height + lineskip);
    }
    if(texInitX){
        *texInitX = abs(cIns_xMin);
    }
    if(texInitY){
        *texInitY = abs(cIns_yMin);
    }
}
// */


//
// Positions
//

//
// Texture
//
SDL_Texture* Text_GenTextureUTF8(Text*t, void(*func)(Text*, TextChar*))
{
    Texture tex;
    SDL_Texture *target_prev;
    Glyph *glyph;
    SDL_Rect dest;
    //
    int t_width, t_height;
    //
    int c;
    int cIns_xInit, cIns_yInit;
    TextChar cIns, cIns_prev;
    //
    int lineskip;
    size_t i;

    cIns = (TextChar){};
    Text_MeasureUTF8(t, &cIns_xInit, &cIns_yInit, &t_width, &t_height, func);
    cIns.x = 0;
    cIns.y = 0;
    //
    cIns.rotation = DEG_TO_RAD(*Text_chrRotation(t));
    cIns.rotation_cos = cos(cIns.rotation);
    cIns.rotation_sin = sin(cIns.rotation);
    //
    *Texture_renderer(&tex) = *Text_renderer(t);
    *Texture_raw(&tex) = SDL_CreateTexture(
        *Texture_renderer(&tex),
        TEXT_TEXTURE_PIXELFORMAT,
        TEXT_TEXTURE_ACCESS,
        t_width,
        t_height
    );
    if(!*Texture_raw(&tex)){
        GRAPHICAL_LOG_ERROR("Error while creating texture to Text through Text_TextureUTF8 function: %s\n", SDL_GetError());
        exit(1);
    }
    Texture_Clear(&tex);
    //*
    SDL_SetTextureBlendMode(
        *Texture_raw(&tex),
        SDL_BLENDMODE_BLEND
    );
    // */
    SDL_SetTextureColorMod(
        *Texture_raw(&tex),
        Text_color(t)->r,
        Text_color(t)->g,
        Text_color(t)->b
    );
    SDL_SetTextureAlphaMod(
        *Texture_raw(&tex),
        Text_color(t)->a
    );
    //
    target_prev = SDL_GetRenderTarget(*Texture_renderer(&tex));
    SDL_SetRenderTarget(*Texture_renderer(&tex), *Texture_raw(&tex));
    //* Render the texture's size
    SDL_SetRenderDrawColor(*Texture_renderer(&tex), 0, 0, 0, 255);
    SDL_RenderClear(*Texture_renderer(&tex));
    // */

    // printf("Text_GenTextureUTF8: %i %i\n", cIns_xInit, cIns_yInit);
    lineskip = *Text_lineskip(t);
    i = 0;
    cIns_prev = cIns;
    while((c = Text_getUTF8(t, (i++))) != '\0'){
        // printf("Text_GenTextureUTF8: %.2lf %.2lf\n", cIns.x, cIns.y);
        cIns.c = c;
        cIns.idx = i - 1;
        if(func){
            func(t, &cIns);
        }
        if(cIns.rotation != cIns_prev.rotation){
            cIns.rotation_cos = cos(cIns.rotation);
            cIns.rotation_sin = sin(cIns.rotation);
        }

        if(c == '\n'){
            cIns.x = 0;
            cIns.y += lineskip * *Text_scaleHeight(t);
            continue;
        }

        glyph = TextCache_GetGlyph(*Text_cache(t), c, *Text_chrFmt(t));
        //*
        cIns.width =
            (
            glyph->w  * fabs(cIns.rotation_cos) * *Text_scaleWidth(t)
            + glyph->h  * fabs(cIns.rotation_sin) * *Text_scaleHeight(t)
            );
        cIns.height = 
            (
            glyph->h * fabs(cIns.rotation_cos) * *Text_scaleHeight(t)
            + glyph->w * fabs(cIns.rotation_sin) * *Text_scaleWidth(t)
            );
        // */

        if(cIns.x + cIns.width > t_width){
            cIns.x = 0;
            cIns.y += lineskip * *Text_scaleHeight(t);
        }

        //*

        dest = (SDL_Rect){
            .x = (int)round(cIns.x) + cIns_xInit,
            .y = (int)round(cIns.y) + cIns_yInit,
            .w = (int)round(glyph->w * *Text_scaleWidth(t)),
            .h = (int)round(glyph->h * *Text_scaleHeight(t))
        };

        SDL_RenderCopyEx(
            *Texture_renderer(&tex),
            *TextCache_texture(*Text_cache(t)),
            glyph,
            &dest,
            RAD_TO_DEG(cIns.rotation),
            NULL,
            *Text_chrFlip(t)
        );
        // */
        cIns.x += cIns.width + *Text_chrDist(t);
        cIns_prev = cIns;
    }
    // printf("Text_GenTextureUTF8: %.2lf %.2lf\n", cIns.x, cIns.y);

    SDL_SetRenderTarget(*Texture_renderer(&tex), target_prev);

    return *Texture_raw(&tex);
}

//
Text* Text_Create(TextCache*cache)
{
    Text *n_t;

    n_t = malloc(sizeof(*n_t));

    *Text_cache(n_t) = cache;
    *Text_cacheTexture(n_t) = NULL;
    //
    *Text_raw(n_t) = malloc(sizeof(**Text_raw(n_t)));
    *Text_raw(n_t)[0] = '\0';
    //
    *Text_config(n_t) = (TextConfig){
        .padding = (Padding){},
        .border = (Border){},
        .margin = (Margin){},

        .color = (SDL_Color){0, 0, 0, 255},
        .lineskip = TTF_FontLineSkip(*TextCache_font(cache)),
        .wrap = 0,
        .rotation = 0,
        .flip = SDL_FLIP_NONE,

        .scale_width = 1,
        .scale_height = 1,

        .chr_dist = 0,
        .chr_rotation = 0,
        .chr_fmt = CHAR_FMT_REGULAR,
        .chr_flip = SDL_FLIP_NONE,

        .x = 0,
        .y = 0,
    };

    return n_t;
}

void Text_DrawUTF8(Text*t, char*str, TextConfig tc, void(*func)(Text*, TextChar*))
{
    TextConfig_Populate(&tc, Text_config(t));

    if(!CHAR_FMT_AVAIBLE(tc.chr_fmt) || !utf8size(str)){
        GRAPHICAL_LOG_CRITICAL("Error while drawing text into Text_DrawUTF8: no font format avaible or str empty\n");
        return;
    }

    //*
    if(utf8cmp(str, *Text_raw(t)) || !TextConfig_Equals(&tc, Text_config(t)) || !*Text_cacheTexture(t) || func != NULL){
        if(*Text_cacheTexture(t) != NULL){
            SDL_DestroyTexture(*Text_cacheTexture(t));
        }
        Text_SetUTF8(t, str);
        /*
        printf(
            "TextConfigs:\n"
            "fmt: %i\n"
            "chr_rotation: %.2lf\n"
            "lineskip: %i\n"
            "wrap: %i\n"
            "scale_width: %.2lf\n"
            "sacle_height: %.2lf\n"
            "chr_dist: %i\n",
            *Text_fmt(t),
            *Text_chrRotation(t),
            *Text_lineskip(t),
            *Text_wrap(t),
            *Text_scaleWidth(t),
            *Text_scaleHeight(t),
            *Text_chrDist(t)
        );
        // */
        *Text_config(t) = tc;
        *Text_cacheTexture(t) = Text_GenTextureUTF8(t, func);
    }
    *Text_config(t) = tc;
    SDL_Rect dest;
    SDL_QueryTexture(
        *Text_cacheTexture(t),
        NULL,
        NULL,
        &dest.w,
        &dest.h
    );
    dest.x = *Text_x(t);
    dest.y = *Text_y(t);

    //*
    SDL_RenderCopyEx(
        *Text_renderer(t),
        *Text_cacheTexture(t),
        NULL,
        &dest,
        *Text_rotation(t),
        NULL,
        *Text_flip(t)
    );
    // */
}

void Text_Destroy(Text**t)
{
    free(*Text_raw(*t));
    free(*t);
}
