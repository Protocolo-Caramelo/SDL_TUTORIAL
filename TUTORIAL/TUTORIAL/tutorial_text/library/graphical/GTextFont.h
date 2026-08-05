#ifndef GTEXTCACHE_H
#define GTEXTCACHE_H

#include"GCommons.h"
#include"GTexture.h"

typedef struct TextFont TextFont;
typedef SDL_Rect Glyph;

/*
 * Struct TextFont
 */
#define FONTS_DEFAULT_TEXTURE_WIDTH 1024
#define FONTS_DEFAULT_TEXTURE_HEIGHT 1024
#define FONTS_DEFAULT_GLYPH_INIT 0x20 // ' '
#define FONTS_DEFAULT_GLYPH_END 0xFF // 'ÿ"
#define FONTS_DEFAULT_RAW_COLOR ((SDL_Color){100, 0, 0, 255})
#define FONTS_DEFAULT_RAW_SIZE 1
#define FONTS_DEFAULT_RAW_WRAP 0
#define FONTS_DEFAULT_RAW_PTSIZE 70
#define FONTS_DEFAULT_BACKGROUND_COLOR (SDL_Color){0, 0, 0, 0}

#define FONTS_TEXTURE_PIXELFORMAT SDL_PIXELFORMAT_RGBA8888
#define FONTS_TEXTURE_ACCESS SDL_TEXTUREACCESS_TARGET

struct TextFont {
    Texture texture;
    int texture_width;
    int texture_height;

    Glyph *glyphs;
    int glyphs_init;
    int glyphs_end;

    TTF_Font *raw;
    unsigned ptsize;

    SDL_Renderer *renderer;
};
WRAP_FIELD(TextFont, texture, Texture);
WRAP_FIELD(TextFont, texture.renderer, renderer, SDL_Renderer*);
WRAP_FIELD(TextFont, texture_width, textureWidth, int);
WRAP_FIELD(TextFont, texture_height, textureHeight, int);

WRAP_FIELD(TextFont, glyphs, Glyph*);
WRAP_FIELD(TextFont, glyphs_init, glyphsInit, int);
WRAP_FIELD(TextFont, glyphs_end, glyphsEnd, int);

WRAP_FIELD(TextFont, raw, TTF_Font*);
WRAP_FIELD(TextFont, ptsize, ptsize, unsigned);

static inline size_t TextFont_glyphsSize(TextFont*f)
{
    return *TextFont_glyphsEnd(f) - *TextFont_glyphsInit(f);
}

static inline int TextFont_lineSkip(TextFont*f)
{
    return TTF_FontLineSkip(*TextFont_raw(f));
}


//
// Methods
//
void TextFont_load(TextFont*, char*path);
void TextFont_generate_atlas(TextFont*);

void TextFont_glyphSize(TextFont*, int c, int*, int*);

void TextFont_destroy(TextFont*);

#endif
