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
    TextCharFormat fmt;
    unsigned lineskip;
    unsigned wrap;
    double rotation;
    //
    double scale_width;
    double scale_height;
    //
    int chr_dist;
    double chr_rotation; // deg
    SDL_RendererFlip chr_flip;
};

// 
// Methods
//
int TextConfig_Equals(TextConfig*, TextConfig*);
void TextConfig_Populate(TextConfig*, TextConfig*);

#endif
