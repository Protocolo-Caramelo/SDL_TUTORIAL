#ifndef GTEXT_H
#define GTEXT_H

#include"GCommons.h"
#include"GTexture.h"
#include"GTextCache.h"
#include"GTextConfig.h"
#include"GTextCharFormat.h"

#include<utf8.h>

typedef struct Text Text;

/*
 * Text struct
 */
struct Text {
    TextCache *cache;
    SDL_Texture* cache_texture;

    char *raw;
    TextConfig config;
};
WRAP_FIELD(Text, cache->texture.renderer, renderer, SDL_Renderer*);
WRAP_FIELD(Text, cache, TextCache*);
WRAP_FIELD(Text, cache_texture, cacheTexture, SDL_Texture*);

WRAP_FIELD(Text, raw, char*);

/* TextConfig struct */
WRAP_FIELD(Text, config, TextConfig);

WRAP_FIELD(Text, config.padding, padding, Padding);
WRAP_FIELD(Text, config.padding.top, paddingTop, unsigned);
WRAP_FIELD(Text, config.padding.right, paddingRight, unsigned);
WRAP_FIELD(Text, config.padding.bottom, paddingBottom, unsigned);
WRAP_FIELD(Text, config.padding.left, paddingLeft, unsigned);
WRAP_FIELD(Text, config.padding.color, paddingColor, SDL_Color);

WRAP_FIELD(Text, config.border, border, TextSpacing);
WRAP_FIELD(Text, config.border.top, borderTop, unsigned);
WRAP_FIELD(Text, config.border.right, borderRight, unsigned);
WRAP_FIELD(Text, config.border.bottom, borderBottom, unsigned);
WRAP_FIELD(Text, config.border.left, borderLeft, unsigned);
WRAP_FIELD(Text, config.border.color, borderColor, SDL_Color);

WRAP_FIELD(Text, config.margin, margin, TextSpacing);
WRAP_FIELD(Text, config.margin.top, marginTop, unsigned);
WRAP_FIELD(Text, config.margin.right, marginRight, unsigned);
WRAP_FIELD(Text, config.margin.bottom, marginBottom, unsigned);
WRAP_FIELD(Text, config.margin.left, marginLeft, unsigned);
WRAP_FIELD(Text, config.margin.color, marginColor, SDL_Color);

WRAP_FIELD(Text, config.color, color, SDL_Color);
WRAP_FIELD(Text, config.lineskip, lineskip, unsigned);
WRAP_FIELD(Text, config.wrap, wrap, unsigned);
WRAP_FIELD(Text, config.rotation, rotation, double);
WRAP_FIELD(Text, config.flip, flip, SDL_RendererFlip);
//
WRAP_FIELD(Text, config.scale_width, scaleWidth, double);
WRAP_FIELD(Text, config.scale_height, scaleHeight, double);

WRAP_FIELD(Text, config.chr_dist, chrDist, int);
WRAP_FIELD(Text, config.chr_rotation, chrRotation, double);
WRAP_FIELD(Text, config.chr_fmt, chrFmt, TextCharFormat);
WRAP_FIELD(Text, config.chr_flip, chrFlip, SDL_RendererFlip);
//
WRAP_FIELD(Text, config.x, x, double);
WRAP_FIELD(Text, config.y, y, double);


//
// Properties
// 
int Text_getUTF8(Text*, size_t );
size_t Text_GetSizeUTF8(Text*t);

char* Text_GetUTF8(Text*t);
void Text_SetUTF8(Text*t, char*);


// Measures
void Text_MeasureMargin(Text*, int*, int*);
void Text_MeasureBorder(Text*, int*, int*);
void Text_MeasurePadding(Text*, int*, int*);
void Text_MeasureUTF8(Text*, int*, int*);

// Positions
void Text_PositionMargin(Text*, int*, int*);
void Text_PositionBorder(Text*, int*, int*);
void Text_PositionPadding(Text*, int*, int*);
void Text_PositionUTF8(Text*, int*, int*);

// Textures
#define TEXT_TEXTURE_PIXELFORMAT SDL_PIXELFORMAT_RGBA8888
#define TEXT_TEXTURE_ACCESS SDL_TEXTUREACCESS_TARGET
SDL_Texture* Text_GenTextureMargin(Text*);
SDL_Texture* Text_GenTextureBorder(Text*);
SDL_Texture* Text_GenTexturePadding(Text*);
SDL_Texture* Text_GenTextureUTF8(Text*);

//
// Methods
//
Text* Text_Create(TextCache*);
void Text_DrawUTF8(Text*, char*str, TextConfig);
void Text_Destroy(Text**);

#endif
