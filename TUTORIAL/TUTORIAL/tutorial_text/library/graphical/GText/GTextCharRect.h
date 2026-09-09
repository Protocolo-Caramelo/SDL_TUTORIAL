#ifndef GTEXTCHARGLYPH_H
#define GTEXTCHARGLYPH_H

#include"GTextTypedefs.h"

struct TextCharRect {
    Glyph *src; // from cache
    int x, y;
    int width, height;
    double rotation;
    SDL_Color color;
};

#endif
