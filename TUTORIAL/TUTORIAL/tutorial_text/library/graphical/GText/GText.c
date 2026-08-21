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
    int width, height;
    int width_tmp, height_tmp;
    int width_chr, height_chr;
    int lineskip;
    int c;

    width = 0;
    height = lineskip = *Text_lineskip(t);
    width_tmp = height_tmp = 0;
    i = 0;
    while((c = Text_getUTF8(t, (i++))) != '\0'){
        width_chr = height_chr = 0;
        if(c != '\n'){
            TextCache_GetGlyphSize(*Text_cache(t), c, *Text_fmt(t), &width_chr, &height_chr);
        }
        // printf("'%i': %i %i %i\n", c, width_chr, height_chr, lineskip);
        // /*
        if(
            c == '\n' ||
            (*Text_wrap(t) && width_tmp + width_chr > *Text_wrap(t))
        ){
            width = MAX(width_tmp, width);
            height += lineskip * *Text_scaleHeight(t);
            width_tmp = 0;
            // continue;
        }

        width_tmp += width_chr * *Text_scaleWidth(t);
    }
    width = MAX(width_tmp, width);

    if(w){
        *w = width;
    }
    if(h){
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
    Glyph dest;
    int t_width, t_height;
    int c;
    int chr_width, chr_height;
    int lineskip;
    size_t i;

    Text_MeasureUTF8(t, &t_width, &t_height);
    *Texture_renderer(&tex) = *Text_renderer(t);
    *Texture_raw(&tex) = SDL_CreateTexture(
        *Texture_renderer(&tex),
        TEXT_TEXTURE_PIXELFORMAT,
        TEXT_TEXTURE_ACCESS,
        t_width,
        t_height
    );
    target_prev = SDL_GetRenderTarget(*Texture_renderer(&tex));

    SDL_SetRenderTarget(*Texture_renderer(&tex), *Texture_raw(&tex));
    dest = (Glyph){};
    lineskip = *Text_lineskip(t);
    i = 0;
    while((c = Text_getUTF8(t, (i++))) != '\0'){
        if(c == '\n'){
            dest.x = 0;
            dest.y += lineskip * *Text_scaleHeight(t);
            continue;
        }

        glyph = TextCache_GetGlyph(*Text_cache(t), c, *Text_fmt(t));
        dest.w = glyph->w * *Text_scaleWidth(t);
        dest.h = glyph->h * *Text_scaleHeight(t);
        chr_width = abs(
            glyph->w * *Text_scaleWidth(t) * cos(DEG_TO_RAD(*Text_chrRotation(t)))
            + glyph->h * *Text_scaleWidth(t) * sin(DEG_TO_RAD(*Text_chrRotation(t)))
            );
        chr_height = abs(
            glyph->h * *Text_scaleHeight(t) * cos(DEG_TO_RAD(*Text_chrRotation(t)))
            + glyph->w * *Text_scaleHeight(t) * sin(DEG_TO_RAD(*Text_chrRotation(t)))
            );
        // printf("'%i': %i %i %i\n", c, glyph->w, glyph->h, lineskip);
        // printf("'%i': (%i %i)\n", c, chr_width, chr_height);

        if(dest.x + chr_width > t_width){
            dest.x = 0;
            dest.y += lineskip * *Text_scaleHeight(t);
        }

        //*
        SDL_RenderCopyEx(
            *Texture_renderer(&tex),
            *TextCache_texture(*Text_cache(t)),
            glyph,
            &dest,
            *Text_chrRotation(t),
            NULL,
            *Text_chrFlip(t)
        );
        // */
        dest.x += chr_width + *Text_chrDist(t);
    }

    SDL_SetRenderTarget(*Texture_renderer(&tex), target_prev);
    SDL_SetTextureBlendMode(
        *Texture_raw(&tex),
        SDL_BLENDMODE_BLEND
    );
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

    return *Texture_raw(&tex);
}

//
Text* Text_Create(TextCache*cache)
{
    Text *n_t;

    n_t = malloc(sizeof(*n_t));
    memset(n_t, 0, sizeof(*n_t));

    *Text_cache(n_t) = cache;
    *Text_cacheTexture(n_t) = NULL;
    *Text_raw(n_t) = malloc(sizeof(**Text_raw(n_t)));
    *Text_fmt(n_t) = CHAR_FMT_REGULAR;
    *Text_lineskip(n_t) = TTF_FontLineSkip(*TextCache_font(cache));
    *Text_scaleWidth(n_t) = 1;
    *Text_scaleHeight(n_t) = 1;

    *Text_raw(n_t)[0] = '\0';

    return n_t;
}

void Text_DrawUTF8(Text*t, char*str, TextConfig tc)
{
    TextConfig_Populate(&tc, Text_config(t));

    if(!CHAR_FMT_AVAIBLE(tc.fmt) || !utf8size(str)){
        GRAPHICAL_LOG_CRITICAL("Error while drawing text into Text_DrawUTF8: no font format avaible or str empty\n");
        return;
    }

    //*
    if(utf8cmp(str, *Text_raw(t)) || !TextConfig_Equals(&tc, Text_config(t)) || !*Text_cacheTexture(t)){
        if(*Text_cacheTexture(t)){
            SDL_DestroyTexture(*Text_cacheTexture(t));
        }
        Text_SetUTF8(t, str);
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
        *Text_config(t) = tc;
        *Text_cacheTexture(t) = Text_GenTextureUTF8(t);
    }
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

    SDL_RenderCopyEx(
        *Text_renderer(t),
        *Text_cacheTexture(t),
        NULL,
        &dest,
        *Text_rotation(t),
        NULL,
        *Text_flip(t)
    );
}

void Text_Destroy(Text**t)
{
    free(*Text_raw(*t));
    free(*t);
}
