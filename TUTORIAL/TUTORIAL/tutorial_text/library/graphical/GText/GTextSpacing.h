#ifndef GTEXTSPACING_H
#define GTEXTSPACING_H

#include"GCommons.h"
#include"GTextTypedefs.h"
#include<SDL2/SDL_pixels.h>

/*
 * TextSpacing Struct
 */
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
int TextSpacing_Equals(TextSpacing*a, TextSpacing*b);
int TextSpacing_Zered(TextSpacing*a);

#endif
