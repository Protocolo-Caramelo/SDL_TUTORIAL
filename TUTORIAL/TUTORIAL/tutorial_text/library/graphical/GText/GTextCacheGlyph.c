#include"GTextCacheGlyph.h"

//
// Properties
//
Glyph *TextCG_GetGlyph(TextCG*g, int c, TextCharFormat fmt)
{
    TextCG *out;
    TextCG search;

    memset(&search, 0, sizeof(search));
    search.key.c = c;
    search.key.fmt = fmt;

    HASH_FIND(hh, g, &search.key, sizeof(search.key), out);
    return (out)? TextCG_cGlyph(out): NULL;
}

Glyph *TextCG_GetGlyphEnd(TextCG*g)
{
    TextCG *bin, *tmp;
    Glyph *glyph;
    Glyph *res;

    res = NULL;
    HASH_ITER(hh, g, bin, tmp){
        glyph = TextCG_cGlyph(bin);
        if(!res){
            res = glyph;
        }

        if(
            (glyph->y >= res->y && glyph->x > res->x)
            || glyph->y > res->y
        ){
            res = glyph;
        }
    }

    return res;
}

size_t TextCG_GetGlyphAmt(TextCG*g)
{
    return HASH_COUNT(g);
}

//
// Methods
//
void TextCG_AddGlyph(TextCG**g, int c, TextCharFormat fmt, Glyph glyph)
{
    if(TextCG_GetGlyph(*g, c, fmt) != NULL){
        GRAPHICAL_LOG_CRITICAL("Character '%i' already into Text's Alta's Glyph Hash\n", c);
        return;
    }

    TextCG *n_tfag;
    n_tfag = malloc(sizeof(TextCG));
    memset(n_tfag, 0, sizeof(*n_tfag));
    n_tfag->key.c = c;
    n_tfag->key.fmt = fmt;
    n_tfag->c_glyph = glyph;

    HASH_ADD(hh, *g, key, sizeof(n_tfag->key), n_tfag);
}

void TextCG_Destroy(TextCG**g)
{
    TextCG *bin, *tmp;
    HASH_ITER(hh, *g, bin, tmp) {
        free(bin);
    }
}
