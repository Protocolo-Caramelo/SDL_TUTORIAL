#ifndef TEXTCHARINSTANCE_H
#define TEXTCHARINSTANCE_H

#include"GTextCharFormat.h"

typedef struct TextChar TextChar;

struct TextChar {
    int c;
    int width;
    int height;
    double rotation;
    double rotation_cos;
    double rotation_sin;
    TextCharFormat fmt;
    SDL_Color color;

    size_t idx;

    double x, y;
};

#endif
