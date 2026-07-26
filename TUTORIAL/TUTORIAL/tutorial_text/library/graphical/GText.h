#ifndef GTEXT_H
#define GTEXT_H

#include"GCommons.h"
#include"GTexture.h"

typedef struct Text Text;
typedef struct TextFont TextFont;
typedef struct TextSpacing TextSpacing;
typedef struct TextVTable TextVTable;

/*
 *  Text proportion from font normal size.
 *  So 1 is normal size, 2 is the double of normal size of font
 *  1 / 2 if half of normal size
 */
typedef double T_TEXTSIZE;
typedef uint16_t T_TEXTWRAP;
typedef uint16_t T_TEXTSPACING;

#define SPACING_AMT 4
typedef enum Spacing Spacing;

/*
 * TextVTable struct
 */
struct TextVTable {
    void (*init)(Text*);
    void (*exit)(Text*);
    void (*render)(Text*);
    void (*event)(Text*, SDL_Event);
};

/*
 * TextSpacing struct
 */
enum Spacing {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
};

struct TextSpacing {
    T_TEXTSPACING left;
    T_TEXTSPACING right;
    T_TEXTSPACING top;
    T_TEXTSPACING bottom;

    SDL_Color color;
};

static inline T_TEXTSPACING* TextSpacing_side(TextSpacing* tsp, Spacing s)
{
    return (s == LEFT)? &tsp->left: (s == RIGHT)? &tsp->right:
            (s == TOP)? &tsp->top: (s == BOTTOM)? &tsp->bottom: NULL;
}

/*
 * TextFont struct
 */
struct TextFont {
    TTF_Font *raw;
    SDL_Color raw_color;
    SDL_Color raw_backgroundColor;

    T_TEXTSIZE raw_size;
    T_TEXTWRAP raw_wrap;

    T_TEXTSIZE raw_width;
    T_TEXTSIZE raw_height;
};

/*
 * Text struct
 */
struct Text {
    TextVTable *vtable;
    SDL_Renderer *renderer;

    char *raw;
    TextFont font;
    TextSpacing padding;
    TextSpacing border;
    TextSpacing margin;

    int x;
    int y;
};

//
// Attributes
//
static inline TextVTable** Text_vtable(Text*t)
{
    return &t->vtable;
}

static inline char** Text_raw(Text*t)
{
    return &t->raw;
}

// Attribute Font
static inline TTF_Font** Text_font(Text*t)
{
    return &t->font.raw;
}

static inline SDL_Color* Text_fontColor(Text*t)
{
    return &t->font.raw_color;
}

static inline SDL_Color* Text_fontBackgroundColor(Text*t)
{
    return &t->font.raw_backgroundColor;
}

static inline T_TEXTSIZE* Text_fontSize(Text*t)
{
    return &t->font.raw_size;
}

static inline T_TEXTWRAP* Text_fontWrap(Text*t)
{
    return &t->font.raw_wrap;
}

// Attribute text box
static inline TextSpacing* Text_paddingRaw(Text*t)
{
    return &t->padding;
}

static inline TextSpacing* Text_borderRaw(Text*t)
{
    return &t->border;
}

static inline TextSpacing* Text_marginRaw(Text*t)
{
    return &t->margin;
}


static inline T_TEXTSPACING* Text_padding(Text*t, Spacing s)
{
    return TextSpacing_side(&t->padding, s);
}

static inline T_TEXTSPACING* Text_border(Text*t, Spacing s)
{
    return TextSpacing_side(&t->border, s);
}

static inline T_TEXTSPACING* Text_margin(Text*t, Spacing s)
{
    return TextSpacing_side(&t->margin, s);
}


static inline SDL_Color* Text_paddingColor(Text*t)
{
    return &t->padding.color;
}

static inline SDL_Color* Text_borderColor(Text*t)
{
    return &t->border.color;
}

static inline SDL_Color* Text_marginColor(Text*t)
{
    return &t->margin.color;
}

// Attribute position
static inline int* Text_x(Text*t)
{
    return &t->x;
}

static inline int* Text_y(Text*t)
{
    return &t->y;
}

// Others
static inline SDL_Renderer** Text_renderer(Text*t)
{
    return &t->renderer;
}

//
// Properties
// 
#define MAX(a, b) ((a) > (b)? (a): (b))

// Measures
void Text_measureFont(Text*, int*, int*);
void Text_measurePadding(Text*, int*, int*);
void Text_measureBorder(Text*, int*, int*);
void Text_measureMargin(Text*, int*, int*);

// Positions
void Text_positionFont(Text*, int*, int*);
void Text_positionPadding(Text*, int*, int*);
void Text_positionBorder(Text*, int*, int*);
void Text_positionMargin(Text*, int*, int*);

// Textures
#define TEXT_TEXTURE_PIXELFORMAT SDL_PIXELFORMAT_RGBA8888
#define TEXT_TEXTURE_ACCESS SDL_TEXTUREACCESS_TARGET
Texture Text_textureFont(Text*);
Texture Text_texturePadding(Text*);
Texture Text_textureBorder(Text*);
Texture Text_textureMargin(Text*);


//
// Access virtuals methods
//
static inline void Text_init(Text*t)
{
    t->vtable->init(t);
}

static inline void Text_exit(Text*t)
{
    t->vtable->exit(t);
}

static inline void Text_render(Text*t)
{
    t->vtable->render(t);
}

static inline void Text_event(Text*t, SDL_Event e)
{
    t->vtable->event(t, e);
}

#endif
