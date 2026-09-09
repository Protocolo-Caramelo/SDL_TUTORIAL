#ifndef GTEXTCHARGLYPH_H
#define GTEXTCHARGLYPH_H

#include"GTextTypedefs.h"

struct TextCharRect {
    Glyph *src;
    int x, y;
    int width, height;
    double rotation;
};

#endif
