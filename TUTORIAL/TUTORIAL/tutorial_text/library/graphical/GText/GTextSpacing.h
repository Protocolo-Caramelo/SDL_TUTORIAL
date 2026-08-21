#ifndef GTEXTSPACING_H
#define GTEXTSPACING_H

#include"GCommons.h"

typedef struct TextSpacing TextSpacing;
typedef enum Spacing Spacing;

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
