#include"GText.h"

static int draw_xInit, draw_yInit;
static int (*draw_edges)[4] = NULL;
static TextCharRect *chrs_dest = NULL;

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
void Text_MeasureUTF8(Text*t, int*w, int*h)
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
    TextChar cIns, cIns_ctrl;
    //

    lineskip = *Text_lineskip(t) * *Text_scaleHeight(t);
    //
    cIns_ctrl = (TextChar){};
    cIns_ctrl.rotation = DEG_TO_RAD(*Text_chrRotation(t));
    cIns_ctrl.rotation_cos = cos(cIns.rotation);
    cIns_ctrl.rotation_sin = sin(cIns.rotation);
    cIns_ctrl.chr_textIdx = 0;
    cIns_ctrl.chr_lineIdx = 0;
    cIns_ctrl.line_idx = 0;
    cIns_ctrl.x = 0;
    cIns_ctrl.y = 0;
    //
    if(chrs_dest != NULL){
        free(chrs_dest);
    }
    chrs_dest = malloc(sizeof(TextCharRect) * Text_GetSizeUTF8(t));

    cIns_xMax = cIns_xMin = cIns_yMax = cIns_yMin = 0;

    //
    i = 0;
    while((c = Text_getUTF8(t, (i++))) != '\0'){
        // printf("Text_MeasureUTF8: %.2lf %.2lf\n", cIns.x, cIns.y);
        c_glyph = TextCache_GetGlyph(*Text_cache(t), c, *Text_chrFmt(t));

        cIns_ctrl.chr = c;
        cIns_ctrl.width = c_glyph->w * *Text_scaleWidth(t);
        cIns_ctrl.height = c_glyph->h * *Text_scaleHeight(t);
        //*
        cIns_ctrl.box_width =
            (
            cIns_ctrl.width * fabs(cIns_ctrl.rotation_cos)
            + cIns_ctrl.height * fabs(cIns_ctrl.rotation_sin)
            );
        cIns_ctrl.box_height = 
            (
            cIns_ctrl.height * fabs(cIns_ctrl.rotation_cos)
            + cIns_ctrl.width * fabs(cIns_ctrl.rotation_sin)
            );
        if(*Text_wrap(t) && cIns.x + cIns.box_width > *Text_wrap(t)){
            cIns_ctrl.y += lineskip;
            cIns_ctrl.x = 0;
            cIns_ctrl.chr_lineIdx = 0;
            cIns_ctrl.line_idx++;
        }
        // */
        // Process the alternate function
        cIns = cIns_ctrl;
        if(*Text_fAlterText(t)){
            (*Text_fAlterText(t))(t, &cIns);
        }
        //*
        if(cIns.rotation != cIns_ctrl.rotation){
            cIns.rotation_cos = cos(cIns.rotation);
            cIns.rotation_sin = sin(cIns.rotation);
        }
        // */
        cIns.box_width =
            (
            cIns.width * fabs(cIns.rotation_cos)
            + cIns.height * fabs(cIns.rotation_sin)
            );
        cIns.box_height = 
            (
            cIns.height * fabs(cIns.rotation_cos)
            + cIns.width * fabs(cIns.rotation_sin)
            );
        if(
            c == '\n' ||
            (*Text_wrap(t) && cIns.x + cIns.box_width > *Text_wrap(t))
        ){
            cIns.y += lineskip;
            cIns.x = 0;
            cIns.chr_lineIdx = 0;
            cIns.line_idx++;
            //
            cIns_ctrl.y += lineskip;
            cIns_ctrl.x = 0;
            cIns_ctrl.chr_lineIdx = 0;
            cIns_ctrl.line_idx++;
        } 

        // Update edges
        if(cIns.x + cIns_ctrl.width + 1 > cIns_xMax){
            cIns_xMax = cIns.x + cIns_ctrl.width + 1;
            // printf("Text_MeasureUTF8: (%2lf %2lf), (%i, %i)\n", cIns_ctrl.x, cIns_ctrl.y, cIns.width, cIns_xMax);
        }

        if(cIns.x < cIns_xMin){
            cIns_xMin = cIns.x;
        }
        if(cIns.y + cIns.height - lineskip > cIns_yMax){
            cIns_yMax = cIns.y + cIns.height - lineskip;
        }
        if(cIns.y < cIns_yMin){
            cIns_yMin = cIns.y;
        }

        //
        chrs_dest[i - 1] = (TextCharRect){
            .src = c_glyph,
            .x = cIns.x,
            .y = cIns.y,
            .width = cIns.width,
            .height = cIns.height,
            .rotation = cIns.rotation,
        };

        // Compute the distance
        if(cIns_ctrl.rotation != cIns.rotation){
            cIns_ctrl.rotation = cIns.rotation;
            cIns_ctrl.rotation_cos = cIns.rotation_cos;
            cIns_ctrl.rotation_sin = cIns.rotation_sin;
        }
        cIns_ctrl.x += cIns.box_width + *Text_chrDist(t);
        ++cIns_ctrl.chr_textIdx;
        ++cIns_ctrl.chr_lineIdx;

    }
    width = abs(cIns_xMax) + abs(cIns_xMin);
    height = abs(cIns_yMax) + abs(cIns_yMin); // + *Text_lineskip(t) * *Text_scaleHeight(t);
    draw_xInit = abs(cIns_xMin);
    draw_yInit = abs(cIns_yMin);
    // printf("Text_MeasureUTF8: x(%i, %i) y(%i %i)\n", cIns_xMax, cIns_xMin, cIns_yMax, cIns_yMin);
    // printf("Text_MeasureUTF8: %i %i\n", width, height);

    if(w){
        *w = (int)floor(width + 1);
    }
    if(h){
        *h = (int)floor(height + lineskip);
    }

    if(draw_edges != NULL){
        (*draw_edges)[DRAW_EDGE_XMAX] = cIns_xMax;
        (*draw_edges)[DRAW_EDGE_XMIN] = cIns_xMin;
        (*draw_edges)[DRAW_EDGE_YMAX] = cIns_yMax + lineskip;
        (*draw_edges)[DRAW_EDGE_YMIN] = cIns_yMin;
    }
}
// */


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
    TextChar cIns, cIns_ctrl;
    //
    int lineskip;
    size_t i;
    //

    Text_MeasureUTF8(t, &t_width, &t_height);
    // cIns
    cIns_ctrl = (TextChar){};
    cIns_ctrl.color = *Text_color(t);
    cIns_ctrl.rotation = DEG_TO_RAD(*Text_chrRotation(t));
    cIns_ctrl.rotation_cos = cos(cIns.rotation);
    cIns_ctrl.rotation_sin = sin(cIns.rotation);
    cIns_ctrl.chr_textIdx = 0;
    cIns_ctrl.chr_lineIdx = 0;
    cIns_ctrl.line_idx = 0;
    cIns_ctrl.x = 0;
    cIns_ctrl.y = 0;
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
    //
    target_prev = SDL_GetRenderTarget(*Texture_renderer(&tex));
    SDL_SetRenderTarget(*Texture_renderer(&tex), *Texture_raw(&tex));
    //* Render the texture's size
    SDL_SetRenderDrawColor(*Texture_renderer(&tex), 0, 0, 0, 255);
    SDL_RenderClear(*Texture_renderer(&tex));
    // */

    // printf("Text_GenTextureUTF8: %i %i\n", cIns_xInit, cIns_yInit);
    lineskip = *Text_lineskip(t) * *Text_scaleHeight(t);
    i = 0;
    while((c = Text_getUTF8(t, (i++))) != '\0'){
        // printf("Text_GenTextureUTF8: %.2lf %.2lf\n", cIns.x, cIns.y);
        glyph = TextCache_GetGlyph(*Text_cache(t), c, *Text_chrFmt(t));
        //*
        cIns_ctrl.chr = c;
        cIns_ctrl.width = glyph->w * *Text_scaleWidth(t);
        cIns_ctrl.height = glyph->h * *Text_scaleHeight(t);
        //*
        cIns_ctrl.box_width = 
            (
            cIns.width * fabs(cIns_ctrl.rotation_cos)
            + cIns.height * fabs(cIns_ctrl.rotation_sin)
            );
        cIns_ctrl.box_height = 
            (
            cIns.height * fabs(cIns_ctrl.rotation_cos)
            + cIns.width * fabs(cIns_ctrl.rotation_sin)
            );
        if(cIns_ctrl.x + cIns_ctrl.box_width > t_width || c == '\n'){
            // printf("Text_GenTextureUTF8: (%.2lf %.2lf) (%i %i)\n", cIns_ctrl.x, cIns_ctrl.y, cIns_ctrl.width, t_width);
        // if(cIns_ctrl.x > t_width || c == '\n'){
            cIns_ctrl.y += lineskip;
            cIns_ctrl.x = 0;
            cIns_ctrl.chr_lineIdx = 0;
            cIns_ctrl.line_idx++;
        }
        // */
        //
        cIns = cIns_ctrl;
        if(*Text_fAlterText(t)){
            (*Text_fAlterText(t))(t, &cIns);
        }
        //*
        if(cIns.rotation != cIns_ctrl.rotation){
            cIns.rotation_cos = cos(cIns.rotation);
            cIns.rotation_sin = sin(cIns.rotation);
        }
        // */
        cIns.box_width = 
            (
            cIns.width * fabs(cIns.rotation_cos)
            + cIns.height * fabs(cIns.rotation_sin)
            );
        cIns.box_height = 
            (
            cIns.height * fabs(cIns.rotation_cos)
            + cIns.width * fabs(cIns.rotation_sin)
            );
        if(cIns.x + cIns.box_width > t_width || c == '\n'){
        // if(cIns.x > t_width || c == '\n'){
            cIns.y += lineskip;
            cIns.x = 0;
            cIns.chr_lineIdx = 0;
            cIns.line_idx++;
            //*
            cIns_ctrl.y += lineskip;
            cIns_ctrl.x = 0;
            cIns_ctrl.chr_lineIdx = 0;
            cIns_ctrl.line_idx++;
            // */
        }
        cIns_ctrl.x += cIns.box_width + *Text_chrDist(t);
        ++cIns_ctrl.chr_textIdx;
        ++cIns_ctrl.chr_lineIdx;

        // Create a destine for the character
        dest = (SDL_Rect){
            .x = (int)round(cIns.x) + draw_xInit,
            .y = (int)round(cIns.y) + draw_yInit,
            .w = (int)round(cIns.width),
            .h = (int)round(cIns.height)
        };
        //


        //*
        // Set char color
        SDL_SetTextureColorMod(
            *TextCache_texture(*Text_cache(t)),
            cIns.color.r,
            cIns.color.g,
            cIns.color.b
        );
        SDL_SetTextureAlphaMod(
            *TextCache_texture(*Text_cache(t)),
            cIns.color.a
        );
        //

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

        .func_alterMargin = NULL,
        .func_alterBorder = NULL,
        .func_alterPadding = NULL,
        .func_alterText = NULL,
    };

    return n_t;
}

void Text_DrawUTF8(Text*t, char*str, TextConfig tc, int (*edges)[4])
{
    draw_edges = NULL;
    if(edges != NULL){
        draw_edges = edges;
    }
    
    //
    TextConfig_Populate(&tc, Text_config(t));
    if(!CHAR_FMT_AVAIBLE(tc.chr_fmt) || !utf8size(str)){
        GRAPHICAL_LOG_CRITICAL("Error while drawing text into Text_DrawUTF8: no font format avaible or str empty\n");
        return;
    }

    //* Check if it's necessary create a new texture for text
    if(utf8cmp(str, *Text_raw(t)) || !TextConfig_Equals(&tc, Text_config(t)) || !*Text_cacheTexture(t) || tc.func_alterText != NULL){
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

    // Process the text cordanates
    SDL_Rect dest;
    SDL_QueryTexture(
        *Text_cacheTexture(t),
        NULL,
        NULL,
        &dest.w,
        &dest.h
    );
    dest.x = *Text_x(t) - draw_xInit;
    dest.y = *Text_y(t) - draw_yInit;
    // dest.y = *Text_y(t) ;

    // Edges
    if(draw_edges != NULL){
        (*draw_edges)[DRAW_EDGE_XMAX] += *Text_x(t);
        (*draw_edges)[DRAW_EDGE_XMIN] += *Text_x(t);
        (*draw_edges)[DRAW_EDGE_YMAX] += *Text_y(t);
        (*draw_edges)[DRAW_EDGE_YMIN] += *Text_y(t);
    }

    //* Render text
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
