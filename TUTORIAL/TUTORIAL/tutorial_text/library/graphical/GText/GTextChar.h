#ifndef TEXTCHARINSTANCE_H
#define TEXTCHARINSTANCE_H

#include"TextCharFormat.h"

typedef struct TextChar TextChar;

struct TextChar {
    int width;
    int height;
    double rotation;
    TextCharFormat fmt;
    SDL_Color color;

    int x;
    int y;
};

#endif
