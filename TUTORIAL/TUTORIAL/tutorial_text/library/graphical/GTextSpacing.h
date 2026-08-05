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
WRAP_FIELD(TextSpacing, top, unsigned);
WRAP_FIELD(TextSpacing, right, unsigned);
WRAP_FIELD(TextSpacing, bottom, unsigned);
WRAP_FIELD(TextSpacing, left, unsigned);
WRAP_FIELD(TextSpacing, color, SDL_Color);

#endif
