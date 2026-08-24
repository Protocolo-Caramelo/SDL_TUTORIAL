#ifndef GTEXTFONTGLYPH_H
#define GTEXTFONTGLYPH_H

#include"GCommons.h"
#include"GTextCharFormat.h"
#include"GTextGlyph.h"
#include<uthash.h>

typedef struct TextCacheGlyph TextCG;
typedef struct TextCacheGlyphKey TextCGK;

struct TextCacheGlyphKey{
    int c;
    TextCharFormat fmt;
};

struct TextCacheGlyph {
    TextCGK key;
    Glyph c_glyph;
    UT_hash_handle hh;
};
WRAP_FIELD(TextCG, key, TextCGK);
WRAP_FIELD(TextCG, c_glyph, cGlyph, Glyph);

//
// Properties
//
Glyph *TextCG_GetGlyph(TextCG*, int c, TextCharFormat fmt);
Glyph *TextCG_GetGlyphEnd(TextCG*);
size_t TextCG_GetGlyphAmt(TextCG*);

//
// Methods
//
void TextCG_AddGlyph(TextCG**, int c, TextCharFormat fmt, Glyph);
void TextCG_Destroy(TextCG**);

#endif
