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

void Text_MeasureUTF8(Text*t, int*w, int*h)
{
    size_t i;
    //
    double width, height;
    double width_tmp, height_tmp;
    int lineskip;
    //
    Glyph *c_glyph;
    int c;
    double chr_width, chr_height;
    double chrRotation_rad;

    width = 0;
    height = *Text_lineskip(t) * *Text_scaleHeight(t);
    lineskip = *Text_lineskip(t);
    width_tmp = height_tmp = 0;
    //
    chrRotation_rad = DEG_TO_RAD(*Text_chrRotation(t));
    //
    i = 0;
    while((c = Text_getUTF8(t, (i++))) != '\0'){
        chr_width = chr_height = 0;
        c_glyph = TextCache_GetGlyph(*Text_cache(t), c, *Text_chrFmt(t));

        chr_width =
            (
            c_glyph->w * fabs(cos(chrRotation_rad)) * *Text_scaleWidth(t)
            + c_glyph->h * fabs(sin(chrRotation_rad)) * *Text_scaleHeight(t)
            );
        chr_height = 
            (
            c_glyph->h * fabs(cos(chrRotation_rad)) * *Text_scaleHeight(t)
            + c_glyph->w * fabs(sin(chrRotation_rad)) * *Text_scaleWidth(t)
            );
        // *
        width_tmp += chr_width + *Text_chrDist(t);
        if(
            c == '\n' ||
            (*Text_wrap(t) && width_tmp > *Text_wrap(t))
        ){
            width = MAX(MIN(width_tmp, *Text_wrap(t)), width);
            height += lineskip * *Text_scaleHeight(t);

            if(width_tmp > *Text_wrap(t)){
                width_tmp = chr_width;
            }
            else {
                width_tmp = 0;
            }
        }
        // printf("Text_MeasureUTF8: '%i': (%lf %lf) (%lf %lf)\n", c, chr_width, chr_height, width_tmp - chr_width + *Text_chrDist(t), height - lineskip * *Text_scaleHeight(t));
    }
    width = MAX(width_tmp, width);

    //
    // Rotate text
    //
    width_tmp = floor(width + 1);
    height_tmp = floor(height + lineskip * *Text_scaleHeight(t));

    if(w){
        // *w = (int)floor(width + 1);
        *w = width;
    }
    if(h){
        // *h = (int)floor(height + lineskip * *Text_scaleHeight(t));
        *h = height;
    }
}


//
// Positions
//

//
// Texture
//
SDL_Texture* Text_GenTextureUTF8(Text*t)
{
    Texture tex;
    SDL_Texture *target_prev;
    Glyph *glyph;
    SDL_Rect dest;
    //
    int t_width, t_height;
    //
    int c;
    double chr_w, chr_h;
    double chr_x, chr_y;
    double chrRotation_rad;
    double chrRotation_cos, chrRotation_sin;
    //
    int lineskip;
    size_t i;

    Text_MeasureUTF8(t, &t_width, &t_height);
    //
    // chrRotation_rad = DEG_TO_RAD(*Text_chrRotation(t) + *Text_rotation(t));
    chrRotation_rad = DEG_TO_RAD(*Text_chrRotation(t));
    chrRotation_cos = cos(chrRotation_rad);
    chrRotation_sin = sin(chrRotation_rad);
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
    /*
    SDL_SetRenderDrawColor(*Texture_renderer(&tex), 0, 0, 0, 255);
    SDL_RenderClear(*Texture_renderer(&tex));
    // */

    chr_x = chr_y = 0;
    lineskip = *Text_lineskip(t);
    i = 0;
    // printf("%i %i\n", t_width, t_height);
    while((c = Text_getUTF8(t, (i++))) != '\0'){
        if(c == '\n'){
            chr_x = 0;
            chr_y += lineskip * *Text_scaleHeight(t);
            continue;
        }

        glyph = TextCache_GetGlyph(*Text_cache(t), c, *Text_chrFmt(t));
        //*
        chr_w =
            (
            glyph->w  * fabs(chrRotation_cos) * *Text_scaleWidth(t)
            + glyph->h  * fabs(chrRotation_sin) * *Text_scaleHeight(t)
            );
        chr_h = 
            (
            glyph->h * fabs(chrRotation_cos) * *Text_scaleHeight(t)
            + glyph->w * fabs(chrRotation_sin) * *Text_scaleWidth(t)
            );
        // */

        if(chr_x + chr_w > t_width || chr_y > t_height){
            chr_x = 0;
            chr_y += lineskip * *Text_scaleHeight(t);
        }
        //*
        // printf("Text_DrawUTF8: '%i': (%lf %lf) (%lf %lf)\n", c, chr_w, chr_h, chr_x, chr_y);
        // */

        //*
        dest = (SDL_Rect){
            .x = (int)round(chr_x),
            .y = (int)round(chr_y),
            .w = (int)round(glyph->w * *Text_scaleWidth(t)),
            .h = (int)round(glyph->h * *Text_scaleHeight(t))
        };
        // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        SDL_RenderCopyEx(
            *Texture_renderer(&tex),
            *TextCache_texture(*Text_cache(t)),
            glyph,
            &dest,
            RAD_TO_DEG(chrRotation_rad),
            NULL,
            *Text_chrFlip(t)
        );
        // */
        chr_x += chr_w + *Text_chrDist(t);
    }

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

void Text_DrawUTF8(Text*t, char*str, TextConfig tc)
{
    TextConfig_Populate(&tc, Text_config(t));

    if(!CHAR_FMT_AVAIBLE(tc.chr_fmt) || !utf8size(str)){
        GRAPHICAL_LOG_CRITICAL("Error while drawing text into Text_DrawUTF8: no font format avaible or str empty\n");
        return;
    }

    //*
    if(utf8cmp(str, *Text_raw(t)) || !TextConfig_Equals(&tc, Text_config(t)) || !*Text_cacheTexture(t)){
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
        *Text_cacheTexture(t) = Text_GenTextureUTF8(t);
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
