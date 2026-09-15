#ifndef GTEXTSPACING_H
#define GTEXTSPACING_H

#include"GCommons.h"
#include"GTextTypedefs.h"
#include<SDL2/SDL_pixels.h>
#include<SDL2/SDL_render.h>
#include<limits.h>

/*
 * TextSpacing Struct
 */
#define TEXTSPACING_UNINITIALIZED_VAL INT_MAX
struct TextSpacing {
    unsigned
        top,
        right,
        bottom,
        left;

    SDL_Color color;
};

//
// Methods
//
void TextSpacing_Populate(TextSpacing*a, TextSpacing*b);
int TextSpacing_Equals(TextSpacing*a, TextSpacing*b);
int TextSpacing_Zered(TextSpacing*a);

#endif
