#include"GText.h"

static int draw_xInit, draw_yInit;

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

size_t Text_GetLenUTF8(Text*t)
{
    return utf8size(*Text_raw(t));
}


char* Text_GetUTF8(Text*t)
{
    return *Text_raw(t);
}

void Text_SetUTF8(Text*t, char*str)
{
    t->raw_changed = (*Text_raw(t) != NULL)? utf8cmp(*Text_raw(t), str): 1;
    if(*Text_raw(t)){
        free(*Text_raw(t));
    }

    *Text_raw(t) = malloc(sizeof(**Text_raw(t)) * utf8size(str));
    utf8cpy(*Text_raw(t), str);
}

void Text_UpdateConfig(Text*t, TextConfig*tc)
{
    t->config_changed = TextConfig_Equals(Text_config(t), tc);
    TextConfig_Populate(tc, Text_config(t));
    *Text_config(t) = *tc;
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
    cIns_ctrl.rotation_cos = cos(cIns_ctrl.rotation);
    cIns_ctrl.rotation_sin = sin(cIns_ctrl.rotation);
    //
    cIns_ctrl.fmt = *Text_chrFmt(t);
    cIns_ctrl.color = *Text_color(t);
    //
    cIns_ctrl.chr_textIdx = 0;
    cIns_ctrl.chr_lineIdx = 0;
    cIns_ctrl.line_idx = 0;
    //
    cIns_ctrl.x = 0;
    cIns_ctrl.y = 0;
    //
    cIns_xMax = cIns_xMin = cIns_yMax = cIns_yMin = 0;
    //
    if(*Text_chrsDest(t)){
        free(*Text_chrsDest(t));
        *Text_chrsDest(t) = NULL;
    }
    *Text_chrsDest(t) = malloc(sizeof(TextCharRect) * Text_GetSizeUTF8(t));
    //
    memset(*Text_edges(t), 0, sizeof((*Text_edges(t))[0]) * sizeof(*Text_edges(t)) / sizeof((*Text_edges(t))[0]));

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
        if(*Text_wrap(t) && cIns_ctrl.x + cIns_ctrl.box_width > *Text_wrap(t)){
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

        if(c == '\n' || (c == ' ' && cIns.x == 0)){
            (*Text_chrsDest(t))[i - 1] = (TextCharRect){
                .src = NULL
            };

            continue;
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
        // printf("%p\n", c_glyph);
        (*Text_chrsDest(t))[i - 1] = (TextCharRect){
            .src = c_glyph,
            .x = cIns.x,
            .y = cIns.y,
            .width = cIns.width,
            .height = cIns.height,
            .rotation = cIns.rotation,
            .color = cIns.color
        };
        // printf("%i %i %i\n", cIns.color.r, cIns.color.g, cIns.color.b);

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
    cIns_yMax += lineskip;
    if(*Text_boxWidthText(t) > 0 && cIns_xMax - cIns_xMin > *Text_boxWidthText(t)){
        cIns_xMax = *Text_boxWidthText(t);
        cIns_xMin = 0;
    }
    if(*Text_boxWidthText(t) < 0 && cIns_xMax - cIns_xMin > -*Text_boxWidthText(t)){
        cIns_xMax = 0;
        cIns_xMin = *Text_boxWidthText(t);
    }
    if(*Text_boxHeightText(t) > 0 && cIns_yMax - cIns_yMin + lineskip> *Text_boxHeightText(t)){
        cIns_yMax = *Text_boxHeightText(t);
        cIns_yMin = 0;
    }
    if(*Text_boxHeightText(t) < 0 && cIns_yMax - cIns_yMin < -*Text_boxHeightText(t)){
        cIns_yMax = 0;
        cIns_yMin = *Text_boxHeightText(t);
    }

    width = cIns_xMax - cIns_xMin;
    height = cIns_yMax - cIns_yMin; // + *Text_lineskip(t) * *Text_scaleHeight(t);
    draw_xInit = -cIns_xMin;
    draw_yInit = -cIns_yMin;
    // printf("Text_MeasureUTF8: x(%i, %i) y(%i %i)\n", cIns_xMax, cIns_xMin, cIns_yMax, cIns_yMin);
    // printf("Text_MeasureUTF8: %i %i\n", width, height);

    if(w){
        *w = (int)floor(width + 1);
    }
    if(h){
        *h = (int)floor(height);
    }

    int draw_edge_xSpacing, draw_edge_ySpacing;
    draw_edge_xSpacing = *Text_marginLeft(t) + *Text_borderLeft(t) + *Text_paddingLeft(t);
    draw_edge_ySpacing = *Text_marginTop(t) + *Text_borderTop(t) + *Text_paddingTop(t);
    //
    (*Text_edges(t))[DRAW_EDGE_TEXT_XMAX] = cIns_xMax + *Text_x(t) + draw_edge_xSpacing;
    (*Text_edges(t))[DRAW_EDGE_TEXT_XMIN] = cIns_xMin + *Text_x(t) + draw_edge_xSpacing;
    (*Text_edges(t))[DRAW_EDGE_TEXT_YMAX] = cIns_yMax + *Text_y(t) + draw_edge_ySpacing;
    (*Text_edges(t))[DRAW_EDGE_TEXT_YMIN] = cIns_yMin + *Text_y(t) + draw_edge_ySpacing;
}

void Text_MeasurePadding(Text*t, int*w, int*h)
{
    int t_width, t_height;

    t_width = t_height = 0;
    if(*Text_chrsDest(t) == NULL || t->raw_changed || t->config_changed){
        // printf("1: %p\n", *Text_chrsDest(t));
        Text_MeasureUTF8(t, &t_width, &t_height);
        // printf("2: %p\n", *Text_chrsDest(t));
    }
    else {
        t_width = (*Text_edges(t))[DRAW_EDGE_TEXT_XMAX] - (*Text_edges(t))[DRAW_EDGE_TEXT_XMIN];
        t_height = (*Text_edges(t))[DRAW_EDGE_TEXT_YMAX] - (*Text_edges(t))[DRAW_EDGE_TEXT_YMIN];
    }

    // printf("%i %i\n", t_width, t_height);
    if(w){
        *w = t_width + *Text_paddingLeft(t) + *Text_paddingRight(t);
    }
    if(h){
        *h = t_height + *Text_paddingTop(t) + *Text_paddingBottom(t);
    }
    //*

    (*Text_edges(t))[DRAW_EDGE_PADDING_XMAX] = (*Text_edges(t))[DRAW_EDGE_TEXT_XMAX] + *Text_paddingRight(t);
    (*Text_edges(t))[DRAW_EDGE_PADDING_XMIN] = (*Text_edges(t))[DRAW_EDGE_TEXT_XMIN] - *Text_paddingLeft(t);
    (*Text_edges(t))[DRAW_EDGE_PADDING_YMAX] = (*Text_edges(t))[DRAW_EDGE_TEXT_YMAX] + *Text_paddingBottom(t);
    (*Text_edges(t))[DRAW_EDGE_PADDING_YMIN] = (*Text_edges(t))[DRAW_EDGE_TEXT_YMIN] - *Text_paddingTop(t);
    // */
}

void Text_MeasureBorder(Text*t, int*w, int*h)
{
    Text_MeasurePadding(t, w, h);
    if(w){
        *w += *Text_borderLeft(t) + *Text_borderRight(t);
    }
    if(h){
        *h += *Text_borderTop(t) + *Text_borderBottom(t);
    }

    (*Text_edges(t))[DRAW_EDGE_BORDER_XMAX] = (*Text_edges(t))[DRAW_EDGE_PADDING_XMAX] + *Text_borderRight(t);
    (*Text_edges(t))[DRAW_EDGE_BORDER_XMIN] = (*Text_edges(t))[DRAW_EDGE_PADDING_XMIN] - *Text_borderLeft(t);
    (*Text_edges(t))[DRAW_EDGE_BORDER_YMAX] = (*Text_edges(t))[DRAW_EDGE_PADDING_YMAX] + *Text_borderBottom(t);
    (*Text_edges(t))[DRAW_EDGE_BORDER_YMIN] = (*Text_edges(t))[DRAW_EDGE_PADDING_YMIN] - *Text_borderTop(t);
}

void Text_MeasureMargin(Text*t, int*w, int*h)
{
    Text_MeasureBorder(t, w, h);
    if(w){
        *w += *Text_marginLeft(t) + *Text_marginRight(t);
    }
    if(h){
        *h += *Text_marginTop(t) + *Text_marginBottom(t);
    }
    (*Text_edges(t))[DRAW_EDGE_MARGIN_XMAX] = (*Text_edges(t))[DRAW_EDGE_BORDER_XMAX] + *Text_marginRight(t);
    (*Text_edges(t))[DRAW_EDGE_MARGIN_XMIN] = (*Text_edges(t))[DRAW_EDGE_BORDER_XMIN] - *Text_marginLeft(t);
    (*Text_edges(t))[DRAW_EDGE_MARGIN_YMAX] = (*Text_edges(t))[DRAW_EDGE_BORDER_YMAX] + *Text_marginBottom(t);
    (*Text_edges(t))[DRAW_EDGE_MARGIN_YMIN] = (*Text_edges(t))[DRAW_EDGE_BORDER_YMIN] - *Text_marginTop(t);
}


//
// Positions
//
void Text_PositionMargin(Text*t, int*x, int*y)
{
    if(x){
        *x = *Text_x(t);
    }
    if(y){
        *y = *Text_y(t);
    }
}

void Text_PositionBorder(Text*t, int*x, int*y)
{
    Text_PositionMargin(t, x, y);
    if(x){
        *x += *Text_marginLeft(t);
    }
    if(y){
        *y += *Text_marginTop(t);
    }
}

void Text_PositionPadding(Text*t, int*x, int*y)
{
    Text_PositionBorder(t, x, y);
    if(x){
        *x += *Text_borderLeft(t);
    }
    if(y){
        *y += *Text_borderTop(t);
    }
}

void Text_PositionUTF8(Text*t, int*x, int*y)
{
    Text_PositionPadding(t, x, y);
    if(x){
        *x += *Text_paddingLeft(t);
    }
    if(y){
        *y += *Text_paddingTop(t);
    }
}

//
// Texture
//
SDL_Texture* Text_GenTextureSpacing(Text*t, int w, int h, SDL_Color*c, void(*f_alterTexture)(Text*, Texture*))
{
    SDL_Texture *tex;
    SDL_Texture *target_prev;
    //

    tex = SDL_CreateTexture(
        *Text_renderer(t),
        TEXT_TEXTURE_PIXELFORMAT,
        TEXT_TEXTURE_ACCESS,
        w,
        h
    );
    if(!tex){
        GRAPHICAL_LOG_ERROR("Error while creatinng texture for Margin in Text_GenTextureMargin function: %s\n", SDL_GetError());
        exit(1);
    }
    //*
    SDL_SetTextureBlendMode(
        tex,
        SDL_BLENDMODE_BLEND
    );
    //
    target_prev = SDL_GetRenderTarget(*Text_renderer(t));
    SDL_SetRenderTarget(*Text_renderer(t), tex);
    SDL_SetRenderDrawColor(
        *Text_renderer(t),
        c->r,
        c->g,
        c->b,
        c->a
    );
    SDL_RenderClear(*Text_renderer(t));
    if(f_alterTexture){
        // f_alterTexture(t, tex);
    }
    //
    SDL_SetRenderTarget(*Text_renderer(t), target_prev);
    // */

    return tex;
}

SDL_Texture* Text_GenTextureMargin(Text*t)
{
    int m_w, m_h;

    if(*Text_chrsDest(t) == NULL){
        Text_MeasureMargin(t, &m_w, &m_h);
    }
    else {
        m_w = (*Text_edges(t))[DRAW_EDGE_MARGIN_XMAX] - (*Text_edges(t))[DRAW_EDGE_MARGIN_XMIN];
        m_h = (*Text_edges(t))[DRAW_EDGE_MARGIN_YMAX] - (*Text_edges(t))[DRAW_EDGE_MARGIN_YMIN];
    }

    return Text_GenTextureSpacing(t, m_w, m_h, Text_marginColor(t), *Text_fAlterMargin(t));
}

SDL_Texture* Text_GenTextureBorder(Text*t)
{
    int b_w, b_h;

    if(*Text_chrsDest(t) == NULL){
        Text_MeasureBorder(t, &b_w, &b_h);
    }
    else {
        b_w = (*Text_edges(t))[DRAW_EDGE_BORDER_XMAX] - (*Text_edges(t))[DRAW_EDGE_BORDER_XMIN];
        b_h = (*Text_edges(t))[DRAW_EDGE_BORDER_YMAX] - (*Text_edges(t))[DRAW_EDGE_BORDER_YMIN];
    }

    return Text_GenTextureSpacing(t, b_w, b_h, Text_borderColor(t), *Text_fAlterBorder(t));
}

SDL_Texture* Text_GenTexturePadding(Text*t)
{
    int p_w, p_h;

    if(*Text_chrsDest(t) == NULL){
        Text_MeasurePadding(t, &p_w, &p_h);
    }
    else {
        p_w = (*Text_edges(t))[DRAW_EDGE_PADDING_XMAX] - (*Text_edges(t))[DRAW_EDGE_PADDING_XMIN];
        p_h = (*Text_edges(t))[DRAW_EDGE_PADDING_YMAX] - (*Text_edges(t))[DRAW_EDGE_PADDING_YMIN];
    }
    // printf("%i %i\n", p_w, p_h);

    return Text_GenTextureSpacing(t, p_w, p_h, Text_paddingColor(t), *Text_fAlterPadding(t));
}

SDL_Texture* Text_GenTextureUTF8(Text*t)
{
    Texture tex;
    SDL_Texture *target_prev;
    Glyph *glyph;
    SDL_Rect dest;
    //
    TextCharRect c_rect;
    //
    size_t i;

    //
    if(*Text_chrsDest(t) == NULL){
        Text_MeasureUTF8(t, NULL, NULL);
    }

    *Texture_renderer(&tex) = *Text_renderer(t);
    *Texture_raw(&tex) = SDL_CreateTexture(
        *Texture_renderer(&tex),
        TEXT_TEXTURE_PIXELFORMAT,
        TEXT_TEXTURE_ACCESS,
        (*Text_edges(t))[DRAW_EDGE_TEXT_XMAX] - (*Text_edges(t))[DRAW_EDGE_TEXT_XMIN],
        (*Text_edges(t))[DRAW_EDGE_TEXT_YMAX] - (*Text_edges(t))[DRAW_EDGE_TEXT_YMIN]
    );
    if(!*Texture_raw(&tex)){
        GRAPHICAL_LOG_ERROR("Error while creating texture to Text in Text_GenTextureUTF8 function: %s\n", SDL_GetError());
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
    SDL_SetRenderDrawColor(
        *Texture_renderer(&tex),
        Text_colorBackground(t)->r,
        Text_colorBackground(t)->g,
        Text_colorBackground(t)->b,
        Text_colorBackground(t)->a
    );
    SDL_RenderClear(*Texture_renderer(&tex));
    // */

    // printf("Text_GenTextureUTF8: %i %i\n", cIns_xInit, cIns_yInit);
    i = 0;
    while(i < Text_GetSizeUTF8(t)){
        c_rect = (*Text_chrsDest(t))[i++];

        if(c_rect.src == NULL){
            continue;
        }

        // Create a destine for the character
        dest = (SDL_Rect){
            .x = (int)round(c_rect.x) + draw_xInit,
            .y = (int)round(c_rect.y) + draw_yInit,
            .w = (int)round(c_rect.width),
            .h = (int)round(c_rect.height)
        };
        //


        //*
        // Set char color
        /*
        printf(
            "%i %i %i\n",
            c_rect.color.r,
            c_rect.color.g,
            c_rect.color.b
        );
        // */
        SDL_SetTextureColorMod(
            *TextCache_texture(*Text_cache(t)),
            c_rect.color.r,
            c_rect.color.g,
            c_rect.color.b
        );
        SDL_SetTextureAlphaMod(
            *TextCache_texture(*Text_cache(t)),
            c_rect.color.a
        );
        //

        // printf("%p\n", c_rect.src.x);
        //*
        SDL_RenderCopyEx(
            *Texture_renderer(&tex),
            *TextCache_texture(*Text_cache(t)),
            c_rect.src,
            &dest,
            RAD_TO_DEG(c_rect.rotation),
            NULL,
            *Text_chrFlip(t)
        );
        // */
    }
    // printf("============\n");
    // printf("Text_GenTextureUTF8: %.2lf %.2lf\n", cIns.x, cIns.y);
    SDL_SetTextureColorMod(
        *TextCache_texture(*Text_cache(t)),
        255,
        255,
        255
    );
    SDL_SetTextureAlphaMod(
        *TextCache_texture(*Text_cache(t)),
        255
    );
    SDL_SetRenderTarget(*Texture_renderer(&tex), target_prev);

    free(*Text_chrsDest(t));
    *Text_chrsDest(t) = NULL;

    return *Texture_raw(&tex);
}

//
// Methods
//
Text* Text_Create(TextCache*cache)
{
    Text *n_t;

    n_t = malloc(sizeof(*n_t));

    *Text_cache(n_t) = cache;
    *Text_cacheTexture(n_t) =
        *Text_paddingCache(n_t) =
        *Text_borderCache(n_t) =
        *Text_marginCache(n_t) =
        *Text_textCache(n_t) = 
        NULL;
    //
    // *Text_raw(n_t) = malloc(sizeof(**Text_raw(n_t)));
    // *Text_raw(n_t)[0] = '\0';
    *Text_raw(n_t) = NULL;
    //
    *Text_chrsDest(n_t) = NULL;
    memset(*Text_edges(n_t), 0, sizeof(*Text_edges(n_t)));
    // *Text_edges(n_t) = NULL;
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

        .bx_width = 0,
        .bx_height = 0,

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

void Text_DrawUTF8(Text*t, char*str, TextConfig *tc, int (*edges)[20])
{
    //*

    if(!tc){
        tc = Text_config(t);
    }

    if(!str){
        str = *Text_raw(t);
    }
    
    //
    TextConfig_Populate(tc, Text_config(t));
    if(!CHAR_FMT_AVAIBLE(tc->chr_fmt)){
        GRAPHICAL_LOG_CRITICAL("Error while drawing text into Text_DrawUTF8: no font format avaible\n");
        return;
    }

    // Prev values of text's config and string content
    SDL_Rect dest;
    SDL_Texture *target_prev;
    int tex_width, tex_height;
    //
    int textRaw_changed;
    int textConfig_changed;
    int textConfig_textuallyChanged;
    int textPadding_changed;
    int textBorder_changed;
    int textMargin_changed;

    //* Check if it's necessary create a new texture for margin, padding, border and/or text
    draw_xInit = draw_yInit = 0;
    //
    textRaw_changed = (*Text_raw(t) != NULL)? utf8cmp(*Text_raw(t), str): 1;
    textConfig_changed = !TextConfig_Equals(tc, Text_config(t));
    textConfig_textuallyChanged = !TextConfig_TextuallyEquals(tc, Text_config(t));
    textMargin_changed = !TextSpacing_Equals(&tc->margin, Text_margin(t));
    textBorder_changed = !TextSpacing_Equals(&tc->border, Text_border(t));
    textPadding_changed = !TextSpacing_Equals(&tc->padding, Text_padding(t));

    // Check
    if(textConfig_changed){
        *Text_config(t) = *tc;
    }
    *Text_rotation(t) = tc->rotation;
    *Text_x(t) = tc->x;
    *Text_y(t) = tc->y;
    *Text_fAlterText(t) = tc->func_alterText;
    *Text_fAlterPadding(t) = tc->func_alterPadding;
    *Text_fAlterBorder(t) = tc->func_alterBorder;
    *Text_fAlterMargin(t) = tc->func_alterMargin;
    // */

    //*
    if(
        textRaw_changed
        || textConfig_changed
        || edges != NULL
        || *Text_cacheTexture(t) == NULL
        //
        || tc->func_alterText != NULL
        || tc->func_alterPadding != NULL
        || tc->func_alterBorder != NULL
        || tc->func_alterMargin != NULL
        ){
        if(textRaw_changed){
            Text_SetUTF8(t, str);
        }
        Text_MeasureMargin(t, &tex_width, &tex_height);
    }
    // */

    //* Margin
    if(
        (
         textMargin_changed
         || textRaw_changed
         || tc->func_alterMargin != NULL
         || tc->func_alterText != NULL
        )
        &&
        (
         *Text_marginTop(t) != 0
         || *Text_marginRight(t) != 0
         || *Text_marginBottom(t) != 0
         || *Text_marginLeft(t) != 0
        )
    ){
        if(*Text_marginCache(t) != NULL){
            SDL_DestroyTexture(*Text_marginCache(t));
            *Text_marginCache(t) = NULL;
        }
        // printf("margin\n");
        *Text_marginCache(t) = Text_GenTextureMargin(t);
    }
    // */

    //* Border
    if(
        (
         textBorder_changed
         || textRaw_changed
         || tc->func_alterBorder != NULL
         || tc->func_alterText != NULL
        )
        &&
        (
         *Text_borderTop(t) != 0
         || *Text_borderRight(t) != 0
         || *Text_borderBottom(t) != 0
         || *Text_borderLeft(t) != 0
        )
    ){
        if(*Text_borderCache(t) != NULL){
            SDL_DestroyTexture(*Text_borderCache(t));
            *Text_borderCache(t) = NULL;
        }
        // printf("border\n");
        *Text_borderCache(t) = Text_GenTextureBorder(t);
    }
    // */

    //* Padding
    if(
        (
         textPadding_changed
         || textRaw_changed
         || tc->func_alterPadding != NULL
         || tc->func_alterText != NULL
        )
        &&
        (
         *Text_paddingTop(t) != 0
         || *Text_paddingRight(t) != 0
         || *Text_paddingBottom(t) != 0
         || *Text_paddingLeft(t) != 0
        )
        ){
        if(*Text_paddingCache(t) != NULL){
            SDL_DestroyTexture(*Text_paddingCache(t));
            *Text_paddingCache(t) = NULL;
        }
        // printf("padding\n");
        *Text_paddingCache(t) = Text_GenTexturePadding(t);
    }
    // */

    //* Text
    if(
        (
         textRaw_changed
         || textConfig_textuallyChanged
         || *Text_textCache(t) == NULL
         || tc->func_alterText != NULL
        )
        && *Text_raw(t)
    ){
        if(*Text_textCache(t) != NULL){
            SDL_DestroyTexture(*Text_textCache(t));
            *Text_textCache(t) = NULL;
        }
        // printf("text %i %i\n", textRaw_changed, textConfig_textuallyChanged);
        *Text_textCache(t) = Text_GenTextureUTF8(t);
    }
    // */

    // Edges
    //*
    (*Text_edges(t))[DRAW_EDGE_XMAX] = (*Text_edges(t))[DRAW_EDGE_MARGIN_XMAX];
    (*Text_edges(t))[DRAW_EDGE_XMIN] = (*Text_edges(t))[DRAW_EDGE_MARGIN_XMIN];
    (*Text_edges(t))[DRAW_EDGE_YMAX] = (*Text_edges(t))[DRAW_EDGE_MARGIN_YMAX];
    (*Text_edges(t))[DRAW_EDGE_YMIN] = (*Text_edges(t))[DRAW_EDGE_MARGIN_YMIN];
    // */

    //* Clean texture that have no size
    // margin
    if(
        *Text_marginCache(t)
        && *Text_marginTop(t) == 0
        && *Text_marginRight(t) == 0
        && *Text_marginBottom(t) == 0
        && *Text_marginLeft(t) == 0
      ){
        SDL_DestroyTexture(*Text_marginCache(t));
        *Text_marginCache(t) = NULL;
    }

    // border
    if(
        *Text_borderCache(t)
        && *Text_borderTop(t) == 0
        && *Text_borderRight(t) == 0
        && *Text_borderBottom(t) == 0
        && *Text_borderLeft(t) == 0
      ){
        SDL_DestroyTexture(*Text_borderCache(t));
        *Text_borderCache(t) = NULL;
    }

    // padding
    if(
        *Text_paddingCache(t)
        && *Text_paddingTop(t) == 0
        && *Text_paddingRight(t) == 0
        && *Text_paddingBottom(t) == 0
        && *Text_paddingLeft(t) == 0
      ){
        SDL_DestroyTexture(*Text_paddingCache(t));
        *Text_paddingCache(t) = NULL;
    }
    // */

    //* Generate a general cache texture for text
    if(
        textRaw_changed
        || textConfig_changed
        || *Text_cacheTexture(t) == NULL
        //
        || tc->func_alterText != NULL
        || tc->func_alterPadding != NULL
        || tc->func_alterBorder != NULL
        || tc->func_alterMargin != NULL
    ){
        if(*Text_cacheTexture(t) != NULL){
            SDL_DestroyTexture(*Text_cacheTexture(t));
            *Text_cacheTexture(t) = NULL;
        }

        *Text_cacheTexture(t) = SDL_CreateTexture(
            *Text_renderer(t),
            TEXT_TEXTURE_PIXELFORMAT,
            TEXT_TEXTURE_ACCESS,
            tex_width,
            tex_height
        );
        SDL_SetTextureBlendMode(
            *Text_cacheTexture(t),
            SDL_BLENDMODE_BLEND
        );
        target_prev = SDL_GetRenderTarget(*Text_renderer(t));
        SDL_SetRenderTarget(*Text_renderer(t), *Text_cacheTexture(t));
        // Clear texture
        SDL_SetRenderDrawColor(*Text_renderer(t), 255, 255, 255, 0);
        SDL_RenderClear(*Text_renderer(t));

        // Margin
        if(*Text_marginCache(t) != NULL){
            SDL_QueryTexture(
                *Text_marginCache(t),
                NULL,
                NULL,
                &dest.w,
                &dest.h
            );

            // printf("%i %i\n", dest.w, dest.h);
            dest.x = 0;
            dest.y = 0;
            SDL_RenderCopy(
                *Text_renderer(t),
                *Text_marginCache(t),
                NULL,
                &dest
            );
        }

        // Border
        if(*Text_borderCache(t) != NULL){
            SDL_QueryTexture(
                *Text_borderCache(t),
                NULL,
                NULL,
                &dest.w,
                &dest.h
            );

            // printf("%i %i\n", dest.w, dest.h);
            dest.x = *Text_marginLeft(t);
            dest.y = *Text_marginTop(t);
            SDL_RenderCopy(
                *Text_renderer(t),
                *Text_borderCache(t),
                NULL,
                &dest
            );
        }

        // Padding
        if(*Text_paddingCache(t) != NULL){
            SDL_QueryTexture(
                *Text_paddingCache(t),
                NULL,
                NULL,
                &dest.w,
                &dest.h
            );

            // printf("%i %i\n", dest.w, dest.h);
            dest.x = *Text_marginLeft(t) + *Text_borderLeft(t);
            dest.y = *Text_marginTop(t) + *Text_borderTop(t);
            SDL_RenderCopy(
                *Text_renderer(t),
                *Text_paddingCache(t),
                NULL,
                &dest
            );
        }

        // Text
        if(*Text_textCache(t) != NULL){
            Text_PositionUTF8(t, &dest.x, &dest.y);
            SDL_QueryTexture(
                *Text_textCache(t),
                NULL,
                NULL,
                &dest.w,
                &dest.h
            );
            //
            dest.x = *Text_marginLeft(t) + *Text_borderLeft(t) + *Text_paddingLeft(t);
            dest.y = *Text_marginTop(t) + *Text_borderTop(t) + *Text_paddingTop(t);
            //
            SDL_RenderCopy(
                *Text_renderer(t),
                *Text_textCache(t),
                NULL,
                &dest
            );
        }

        //
        SDL_SetRenderTarget(*Text_renderer(t), target_prev);
    }  

    SDL_QueryTexture(
        *Text_cacheTexture(t),
        NULL,
        NULL,
        &dest.w,
        &dest.h
    );
    dest.x = *Text_x(t) - draw_xInit;
    dest.y = *Text_y(t) - draw_yInit;
    // printf("%i %i\n", dest.w, dest.h);
    // printf("%lf\n", *Text_rotation(t));
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

    /*
    if(*Text_chrsDest(t) != NULL){
        free(*Text_chrsDest(t));
        *Text_chrsDest(t) = NULL;
    }
    // */
    if(edges != NULL){
        memcpy(*edges, *Text_edges(t), sizeof(*Text_edges(t)));
    }
}

void Text_Destroy(Text**t)
{
    free(*Text_raw(*t));
    if(*Text_marginCache(*t)){
        SDL_DestroyTexture(*Text_marginCache(*t));
    }
    //*
    if(*Text_borderCache(*t)){
        SDL_DestroyTexture(*Text_borderCache(*t));
    }
    if(*Text_paddingCache(*t)){
        SDL_DestroyTexture(*Text_paddingCache(*t));
    }
    // */
    if(*Text_textCache(*t)){
        SDL_DestroyTexture(*Text_textCache(*t));
    }
    //*
    if(*Text_cacheTexture(*t)){
        SDL_DestroyTexture(*Text_cacheTexture(*t));
    }
    // */

    free(*t);
}
