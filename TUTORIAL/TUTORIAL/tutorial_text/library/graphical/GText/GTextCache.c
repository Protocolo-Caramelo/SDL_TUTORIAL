#include"GTextCache.h"

//
// Properties
//
Glyph* TextCache_GetGlyph(TextCache*a, int c, TextCharFormat fmt)
{
    Glyph *g;
    if((g = TextCG_GetGlyph(*TextCache_glyphs(a), c, fmt)) == NULL){
        TextCache_AddGlyph(a, c, fmt);
    }
    return (g)? g: TextCG_GetGlyph(*TextCache_glyphs(a), c, fmt);
}

size_t TextCache_GetGlyphAmt(TextCache*a)
{
    return TextCG_GetGlyphAmt(*TextCache_glyphs(a));
}

void TextCache_GetGlyphSize(TextCache*a, int c, TextCharFormat fmt, int *w, int *h)
{
    Glyph *g;
    g = TextCache_GetGlyph(a, c, fmt);

    if(w){
        *w = g->w;
    }
    if(h){
        *h = g->h;
    }
}


void TextCache_GetAtlasSize(TextCache*a, int *w, int *h)
{
    int width, height;
    SDL_QueryTexture(
        *TextCache_texture(a),
        NULL,
        NULL,
        &width,
        &height
    );

    if(w){
        *w = width;
    }
    if(h){
        *h = height;
    }
}

void TextCache_SetAtlasSize(TextCache*a, unsigned w, unsigned h)
{
    SDL_Texture *n_tex, *prev_target;
    SDL_Rect dest;
    TextCG *bin, *tmp;
    int lineskip;

    n_tex = SDL_CreateTexture(
        *TextCache_renderer(a),
        TEXTFA_TEXTURE_PIXELFORMAT,
        TEXTFA_TEXTURE_ACCESS,
        w,
        h
    );
    if(!n_tex){
        GRAPHICAL_LOG_ERROR("Error while creating resizing TextCache's texture: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_SetTextureBlendMode(
        n_tex,
        SDL_BLENDMODE_BLEND
    );

    dest = (SDL_Rect){};
    lineskip =TTF_FontLineSkip(*TextCache_font(a));
    prev_target = SDL_GetRenderTarget(*TextCache_renderer(a));

    SDL_SetRenderTarget(*TextCache_renderer(a), n_tex);
    SDL_SetRenderDrawColor(*TextCache_renderer(a), 255, 255, 255, 0);
    SDL_RenderClear(*TextCache_renderer(a));
    HASH_ITER(hh, *TextCache_glyphs(a), bin, tmp) {
        dest.w = TextCG_cGlyph(bin)->w;
        dest.h = TextCG_cGlyph(bin)->h;
        if(dest.x + dest.w > w){
            dest.x = 0;
            dest.y += lineskip;
        }
        // printf("Realloc %i: (%i %i)wh (%i %i)xy\n", TextCG_key(bin)->c, dest.w, dest.h, TextCG_cGlyph(bin)->w, TextCG_cGlyph(bin)->h);

        SDL_RenderCopy(
            *TextCache_renderer(a),
            *TextCache_texture(a),
            TextCG_cGlyph(bin),
            &dest
        );
        *TextCG_cGlyph(bin) = dest;

        dest.x += dest.w;
    }
    SDL_SetRenderTarget(*TextCache_renderer(a), prev_target);

    SDL_DestroyTexture(*TextCache_texture(a));
    *TextCache_texture(a) = n_tex;
}

//
// Methods
//
TextCache* TextCache_Create(SDL_Renderer*r, char *f_path, unsigned ptsize)
{
    TextCache *n_cache;
    SDL_Texture *target_prev;

    n_cache = malloc(sizeof(*n_cache));
    *TextCache_font(n_cache) = TTF_OpenFont(f_path, ptsize);
    *TextCache_renderer(n_cache) = r;
    *TextCache_texture(n_cache) = SDL_CreateTexture(
        r,
        TEXTFA_TEXTURE_PIXELFORMAT,
        TEXTFA_TEXTURE_ACCESS,
        TEXTFA_DEFAULT_TEXTURE_WIDTH,
        TEXTFA_DEFAULT_TEXTURE_HEIGHT
    );
    if(!*TextCache_texture(n_cache)){
        GRAPHICAL_LOG_ERROR("Error while creating texture for cache of font \"%s\" width ptsize %i: %s\n", f_path, ptsize, SDL_GetError());
        exit(1);
    }
    SDL_SetTextureBlendMode(
        *TextCache_texture(n_cache),
        SDL_BLENDMODE_BLEND
    );
    Texture_Clear(&(n_cache->texture));
    if(!*TextCache_font(n_cache)){
        GRAPHICAL_LOG_ERROR("Error while opening TextFontAtla's font: %s\n", SDL_GetError());
        exit(1);
    }
    if(!*TextCache_texture(n_cache)){
        GRAPHICAL_LOG_ERROR("Error while creating TextFontAtla's texture: %s\n", SDL_GetError());
        exit(1);
    }

    *TextCache_glyphs(n_cache) = NULL;

    return n_cache;
}

void TextCache_AddGlyph(TextCache*a, int c, TextCharFormat fmt)
{
    if(TextCG_GetGlyph(*TextCache_glyphs(a), c, fmt) != NULL){
        GRAPHICAL_LOG_CRITICAL("Glyph '%i' already added to TextFontAtlas\n", c);
        return;
    }

    TTF_Font *font;
    int lineskip;
    //
    SDL_Rect dest;
    SDL_Color color;
    //
    SDL_Surface *chr_surf;
    SDL_Texture *chr_tex;
    short unsigned chr_raw[2];
    int chr_width, chr_height;
    //
    SDL_Texture *prev_target;
    Glyph *g_end;
    Glyph g_init;
    int atlas_width, atlas_height;

    font = *TextCache_font(a);
    lineskip = TTF_FontLineSkip(*TextCache_font(a));
    color = TEXTFA_DEFAULT_GLYPH_COLOR;
    g_init = (Glyph){};
    g_end = &g_init;
    if(*TextCache_glyphs(a) != NULL){
        g_end = TextCG_GetGlyphEnd(*TextCache_glyphs(a));
    }
    TextCache_GetAtlasSize(a, &atlas_width, &atlas_height);

    TTF_SetFontStyle(font, fmt);

    // Create texture for char
    chr_raw[0] = c;
    chr_raw[1] = '\0';
    chr_surf = TTF_RenderUNICODE_Blended(
        font, chr_raw, color
    );
    TTF_SizeUNICODE(
        font, chr_raw, &chr_width, &chr_height
    );
    if(!chr_surf){
        GRAPHICAL_LOG_ERROR("Error while rendering char surf for character '%i': %s\n", c, SDL_GetError());
        return;
    }
    // printf("%i: (%i %i); (%i %i)\n", c, chr_width, chr_height, g_end->w, g_end->h);
    chr_tex = SDL_CreateTextureFromSurface(*TextCache_renderer(a), chr_surf);

    // Get Glyph size
    dest.x = g_end->x + g_end->w;
    dest.y = g_end->y;
    dest.w = chr_width;
    dest.h = chr_height;
    if(dest.x + dest.w > atlas_width){
        dest.x = 0;
        dest.y += lineskip;
    }
    // printf("%i: (%i %i)wh (%i %i)xy\n", c, dest.w, dest.h, dest.x, dest.y);

    // Resize if the atla's texture isn't big enough
    // /*
    if(dest.y + chr_height > atlas_height){
        TextCache_SetAtlasSize(
            a,
            (atlas_width * 2 > chr_width)? (atlas_width *= 2): chr_width,
            (atlas_height * 2 > chr_height)? (atlas_height *= 2): chr_height
        );
        g_end = TextCG_GetGlyphEnd(*TextCache_glyphs(a));
        dest.x = dest.y = 0;
        if(g_end != NULL){
            dest.x = g_end->x + g_end->w;
            dest.y = g_end->y;
        }

        if(dest.x + chr_width > atlas_width){
            dest.x = 0;
            dest.y += lineskip;
        }
        if(dest.y + chr_height > atlas_height){
            GRAPHICAL_LOG_ERROR("Error while resize TextFontAtlas for character '%i': Are you really using a good font?\n", c);
            exit(1);
        }
    }
    // */

    // Render Glyph
    prev_target = SDL_GetRenderTarget(*TextCache_renderer(a));
    SDL_SetRenderTarget(*TextCache_renderer(a), *TextCache_texture(a));
    //*
    SDL_RenderCopy(
        *TextCache_renderer(a),
        chr_tex,
        NULL,
        &dest
    );
    // */
    SDL_SetRenderTarget(*TextCache_renderer(a), prev_target);

    SDL_FreeSurface(chr_surf);
    SDL_DestroyTexture(chr_tex);

    // Add c to TextCG
    TextCG_AddGlyph(TextCache_glyphs(a), c, fmt, dest);
    // */
}

void TextCache_Destroy(TextCache**a)
{
    TextCG_Destroy(TextCache_glyphs(*a));
    SDL_DestroyTexture(*TextCache_texture(*a));
    TTF_CloseFont(*TextCache_font(*a));
    free(*a);
}
