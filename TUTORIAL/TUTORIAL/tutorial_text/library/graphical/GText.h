#ifndef GTEXT_H
#define GTEXT_H

#include"GCommons.h"
#include"GTexture.h"
#include"GTextFont.h"
#include"GTextSpacing.h"
#include<utf8.h>

typedef struct Text Text;

/*
 * Text struct
 */
struct Text {
    TextFont *font;
    TextSpacing padding;
    TextSpacing border;
    TextSpacing margin;

    char *raw;

    unsigned wrap;
    double scale;
    int x, y;
};
WRAP_FIELD(Text, font->texture.renderer, renderer, SDL_Renderer*);
WRAP_FIELD(Text, font, TextFont*);

WRAP_FIELD(Text, padding, TextSpacing);
WRAP_FIELD(Text, padding.top, paddingTop, unsigned);
WRAP_FIELD(Text, padding.right, paddingRight, unsigned);
WRAP_FIELD(Text, padding.bottom, paddingBottom, unsigned);
WRAP_FIELD(Text, padding.left, paddingLeft, unsigned);
WRAP_FIELD(Text, padding.color, paddingColor, SDL_Color);

WRAP_FIELD(Text, border, TextSpacing);
WRAP_FIELD(Text, border.top, borderTop, unsigned);
WRAP_FIELD(Text, border.right, borderRight, unsigned);
WRAP_FIELD(Text, border.bottom, borderBottom, unsigned);
WRAP_FIELD(Text, border.left, borderLeft, unsigned);
WRAP_FIELD(Text, border.color, borderColor, SDL_Color);

WRAP_FIELD(Text, margin, TextSpacing);
WRAP_FIELD(Text, margin.top, marginTop, unsigned);
WRAP_FIELD(Text, margin.right, marginRight, unsigned);
WRAP_FIELD(Text, margin.bottom, marginBottom, unsigned);
WRAP_FIELD(Text, margin.left, marginLeft, unsigned);
WRAP_FIELD(Text, margin.color, marginColor, SDL_Color);

WRAP_FIELD(Text, raw, char*);
WRAP_FIELD(Text, wrap, unsigned);
WRAP_FIELD(Text, scale, double);
WRAP_FIELD(Text, x, int);
WRAP_FIELD(Text, y, int);


//
// Properties
// 

// Measures
void Text_measureRaw(Text*, int*, int*);
void Text_measurePadding(Text*, int*, int*);
void Text_measureBorder(Text*, int*, int*);
void Text_measureMargin(Text*, int*, int*);

// Positions
void Text_positionMargin(Text*, int*, int*);
void Text_positionBorder(Text*, int*, int*);
void Text_positionPadding(Text*, int*, int*);
void Text_positionRaw(Text*, int*, int*);

// Textures
#define TEXT_TEXTURE_PIXELFORMAT SDL_PIXELFORMAT_RGBA8888
#define TEXT_TEXTURE_ACCESS SDL_TEXTUREACCESS_TARGET
Texture Text_textureFont(Text*);
Texture Text_texturePadding(Text*);
Texture Text_textureBorder(Text*);
Texture Text_textureMargin(Text*);

#endif
