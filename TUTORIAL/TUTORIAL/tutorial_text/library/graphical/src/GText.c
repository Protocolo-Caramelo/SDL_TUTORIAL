#include<graphical.h>

//
// Properties
// 

// Measures
void Text_measureFont(Text*t, int*w, int*h)
{
    char *text;
    TTF_Font *font;
    int lineSkip, c;
    int right_w, left_w;
    int right_h, left_h;
    int width, height;
    size_t right, left;

    width = height = 0;
    right = left = 0;
    text = *Text_raw(t);
    font = *Text_font(t);
    lineSkip = TTF_FontLineSkip(font);
    while((c = (text)[left]) != '\0'){
        if(c != '\n' && *Text_fontWrap(t) == 0){
            ++left;
            continue;
        }

        if(*Text_fontWrap(t)){
            TTF_SizeUTF8(font, text + left + 1, &left_w, &left_h);
            TTF_SizeUTF8(font, text + right, &right_w, &right_h);
            if(c != '\n' && right_w - left_w <= *Text_fontWrap(t) && *Text_fontWrap(t)){
                ++left;
                continue;
            }
        }
        // Operate a line break
        TTF_SizeUTF8(font, text + left, &left_w, &left_h);
        TTF_SizeUTF8(font, text + right, &right_w, &right_h);

        width = (c == '\n')? MAX(right_w - left_w, width): *Text_fontWrap(t);
        height += lineSkip;
        // printf("%c: %li %i (%i %i)\n", c, left, right_w - left_w, *w, *h);

        ++left;
        // right = left;
        right = (c != '\n' && text[left] != '\0')? left - 1: left;
    }

    TTF_SizeUTF8(font, text + left, &left_w, &left_h);
    TTF_SizeUTF8(font, text + right, &right_w, &right_h);
    width = MAX(right_w - left_w, width);
    height += ((right_w - left_w > 0)? lineSkip: 0);

    if(*Text_fontWrap(t)){
        // *h += (*w > *Text_fontWrap(t))? lineSkip: 0;
        width = (width > *Text_fontWrap(t))? *Text_fontWrap(t): width;
    }

    width *= *Text_fontSize(t);
    height *= *Text_fontSize(t);

    if(w){
        *w = width;
    }
    if(h){
        *h = height;
    }
}

void Text_measurePadding(Text*t, int*w, int*h)
{
    Text_measureFont(t, w, h);
    if(w){
        *w += *Text_padding(t, LEFT) + *Text_padding(t, RIGHT);
    }
    if(h){
        *h += *Text_padding(t, TOP) + *Text_padding(t, BOTTOM);
    }
}

void Text_measureBorder(Text*t, int*w, int*h)
{
    Text_measurePadding(t, w, h);
    if(w){
        *w += *Text_border(t, LEFT) + *Text_border(t, RIGHT);
    }
    if(h){
        *h += *Text_border(t, TOP) + *Text_border(t, BOTTOM);
    }
}

void Text_measureMargin(Text*t, int*w, int*h)
{
    Text_measureBorder(t, w, h);
    if(w){
        *w += *Text_margin(t, LEFT) + *Text_border(t, RIGHT);
    }
    if(h){
        *h += *Text_margin(t, TOP) + *Text_border(t, BOTTOM);
    }
}

// Positions
void Text_positionFont(Text*t, int*x, int*y)
{
    Text_positionPadding(t, x, y);
    if(x){
        *x += *Text_padding(t, LEFT);
    }
    if(y){
        *y += *Text_padding(t, RIGHT);
    }

}

void Text_positionPadding(Text*t, int*x, int*y)
{
    Text_positionBorder(t, x, y);
    if(x){
        *x += *Text_border(t, LEFT);
    }
    if(y){
        *y += *Text_border(t, TOP);
    }
}

void Text_positionBorder(Text*t, int*x, int*y)
{
    Text_positionMargin(t, x, y);
    if(x){
        *x += *Text_margin(t, LEFT);
    }
    if(y){
        *y += *Text_margin(t, TOP);
    }
}

void Text_positionMargin(Text*t, int*x, int*y)
{
    if(x){
        *x = *Text_x(t);
    }
    if(y){
        *y = *Text_y(t);
    }
}

// Textures
Texture Text_textureFont(Text*text)
{
    Texture t;
    SDL_Surface *surf;

    surf = TTF_RenderUTF8_Blended_Wrapped(
        *Text_font(text), *Text_raw(text), *Text_fontColor(text), *Text_fontWrap(text)
    );
    if(!surf){
        printf("Error while creating surface for text \"%s\": %s\n", *Text_raw(text), SDL_GetError());
        exit(1);
    }

    *Texture_renderer(&t) = *Text_renderer(text);
    *Texture_raw(&t) = SDL_CreateTextureFromSurface(
        *Texture_renderer(&t),
        surf
    );
    if(!*Texture_raw(&t)){
        printf("Error while creating texture for text \"%s\": %s\n", *Text_raw(text), SDL_GetError());
        exit(1);
    }

    return t;
}

Texture Text_texturePadding(Text*text)
{
    Texture t;
    SDL_Texture *prev;
    int padding_w, padding_h;

    Text_measurePadding(text, &padding_w, &padding_h);
    *Texture_renderer(&t) = *Text_renderer(text);
    *Texture_raw(&t) = SDL_CreateTexture(
        *Texture_renderer(&t),
        TEXT_TEXTURE_PIXELFORMAT,
        TEXT_TEXTURE_ACCESS,
        padding_w,
        padding_h
    );
    if(!*Texture_raw(&t)){
        printf("Error while creating texture for text's padding \"%s\": %s\n", *Text_raw(text), SDL_GetError());
        exit(1);
    }
    prev = SDL_GetRenderTarget(*Texture_renderer(&t));

    SDL_SetRenderTarget(*Texture_renderer(&t), *Texture_raw(&t));
    SDL_SetRenderDrawColor(
        *Texture_renderer(&t),
        (*Text_paddingColor(text)).r,
        (*Text_paddingColor(text)).g,
        (*Text_paddingColor(text)).b,
        (*Text_paddingColor(text)).a
    );
    SDL_RenderClear(*Texture_renderer(&t));
    SDL_SetRenderTarget(*Texture_renderer(&t), prev);

    SDL_SetTextureBlendMode(
        *Texture_raw(&t),
        SDL_BLENDMODE_BLEND
    );
    SDL_SetTextureAlphaMod(
        *Texture_raw(&t),
        (*Text_paddingColor(text)).a
    );

    return t;
}

Texture Text_textureBorder(Text*t)
{
}

Texture Text_textureMargin(Text*t)
{
}
