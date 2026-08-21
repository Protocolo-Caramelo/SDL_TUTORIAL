#ifndef GTEXTFONTATLAS_H
#define GTEXTFONTATLAS_H

#include"GCommons.h"
#include"GTexture.h"
#include"GTextCharFormat.h"
#include"GTextCacheGlyph.h"

typedef struct TextCache TextCache;

#define TEXTFA_TEXTURE_PIXELFORMAT          SDL_PIXELFORMAT_RGBA8888
#define TEXTFA_TEXTURE_ACCESS               SDL_TEXTUREACCESS_TARGET
#define TEXTFA_DEFAULT_GLYPH_COLOR          (SDL_Color){255, 255, 255, 255}
#define TEXTFA_DEFAULT_TEXTURE_WIDTH        256
#define TEXTFA_DEFAULT_TEXTURE_HEIGHT       256

struct TextCache {
    TTF_Font *font;
    Texture texture;
    TextCG *glyphs;
};
WRAP_FIELD(TextCache, font, TTF_Font*);
WRAP_FIELD(TextCache, texture.renderer, renderer, SDL_Renderer*);
WRAP_FIELD(TextCache, texture.raw, texture, SDL_Texture*);
WRAP_FIELD(TextCache, glyphs, TextCG*);

//
// Properties
// 
#define TEXTFONTATLAS_GLYPH_IN_ATLAS(t, g) \
    ((g) >= *TextFontAtlas_glyphsInit(t) && (g) <= *TextFontAtlas_glyphsEnd(t))
Glyph* TextCache_GetGlyph(TextCache*, int c, TextCharFormat);
size_t TextCache_GetGlyphAmt(TextCache*);
void TextCache_GetGlyphSize(TextCache*, int c, TextCharFormat, int*, int*);

void TextCache_GetAtlasSize(TextCache*, int*, int*);
void TextCache_SetAtlasSize(TextCache*, unsigned, unsigned);

//
// Methods
//
TextCache* TextCache_Create(SDL_Renderer*, char*, unsigned);

void TextCache_AddGlyph(TextCache*, int c, TextCharFormat fmt);
void TextCache_Destroy(TextCache**);

#endif
