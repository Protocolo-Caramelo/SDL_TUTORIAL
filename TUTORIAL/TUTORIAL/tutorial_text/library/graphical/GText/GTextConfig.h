#ifndef GTEXTCONFIG_H
#define GTEXTCONFIG_H

#include"GTextSpacing.h"
#include"GTextCharFormat.h"

typedef struct TextConfig TextConfig;

typedef TextSpacing Padding;
typedef TextSpacing Border;
typedef TextSpacing Margin;

struct TextConfig {
    Padding padding;
    Border border;
    Margin margin;

    SDL_Color color;
    unsigned lineskip;
    unsigned wrap;
    double rotation;
    SDL_RendererFlip flip;
    //
    double scale_width;
    double scale_height;
    //
    int chr_dist;
    double chr_rotation; // deg
    TextCharFormat chr_fmt;
    SDL_RendererFlip chr_flip;
    //
    double x, y;
};

// 
// Methods
//
#define TextConfig_Create(...) (TextConfig){ \
    .padding = (Padding){}, \
    .border = (Border){}, \
    .margin = (Border){}, \
    \
    .color = (SDL_Color){}, \
    .lineskip = 0, \
    .wrap = 0, \
    .rotation = NAN, \
    .flip = (SDL_FLIP_VERTICAL + 1), \
    \
    .scale_width = 0, \
    .scale_height = 0, \
    \
    .chr_dist = 0, \
    .chr_rotation = NAN, \
    .chr_fmt = CHAR_FMT_INVALID, \
    .chr_flip = (SDL_FLIP_VERTICAL + 1), \
    \
    .x = NAN, \
    .y = NAN, \
    ##__VA_ARGS__ \
}

int TextConfig_Equals(TextConfig*, TextConfig*);
void TextConfig_Populate(TextConfig*, TextConfig*);

#endif
