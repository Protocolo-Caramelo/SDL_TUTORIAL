#include<graphical.h>

void TextFont_load(TextFont*f, char*path)
{
    DEFAULT_VALUE(*TextFont_renderer(f), NULL);
    DEFAULT_VALUE(*TextFont_textureWidth(f), FONTS_DEFAULT_TEXTURE_WIDTH);
    DEFAULT_VALUE(*TextFont_textureHeight(f), FONTS_DEFAULT_TEXTURE_HEIGHT);
    DEFAULT_VALUE(*TextFont_glyphsInit(f), FONTS_DEFAULT_GLYPH_INIT);
    DEFAULT_VALUE(*TextFont_glyphsEnd(f), FONTS_DEFAULT_GLYPH_END);
    DEFAULT_VALUE(*TextFont_ptsize(f), FONTS_DEFAULT_RAW_PTSIZE);

    if(!*TextFont_renderer(f)){
        GRAPHICAL_LOG_ERROR("Error while loading font: No renderer passed to font\n");
        exit(1);
    }

    *TextFont_glyphs(f) = malloc(sizeof(**TextFont_glyphs(f)) * TextFont_glyphsSize(f));
    *TextFont_raw(f) = TTF_OpenFont(path, *TextFont_ptsize(f));
    TextFont_generate_atlas(f);
}

void TextFont_generate_atlas(TextFont*f)
{
    int i, j;
    SDL_Rect *glyph;
    SDL_Rect dest;
    SDL_Color white;
    SDL_Surface *s;
    SDL_Surface *chr_surf;
    short unsigned chr_raw[2];
    int lineSkip;

    white  = (SDL_Color){0, 0, 255, 255};
    memset(*TextFont_glyphs(f), 0, sizeof(**TextFont_glyphs(f)) * TextFont_glyphsSize(f));
    s = SDL_CreateRGBSurface(
        0, *TextFont_textureWidth(f), *TextFont_textureHeight(f), 32, 0, 0, 0, 0xff
    );
    SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGBA(s->format, 0, 0, 0, 0));
    lineSkip = TTF_FontLineSkip(*TextFont_raw(f));
    i = *TextFont_glyphsInit(f);
    dest.x = dest.y = 0;
    j = 0;
    while(i <= *TextFont_glyphsEnd(f)){
        chr_raw[0] = i;
        chr_raw[1] = '\0';
        chr_surf = TTF_RenderUNICODE_Blended(
            *TextFont_raw(f), chr_raw, white 
        );
        TTF_SizeUNICODE(
            *TextFont_raw(f), chr_raw, &dest.w, &dest.h
        );
        // printf("%i %i %i\n", chr_raw[0], dest.x, dest.y);

        // 
        if(!chr_surf){
            GRAPHICAL_LOG_CRITICAL("Error while building font's atlas: %s\n", SDL_GetError());
            ++i;
            continue;
        }

        if(dest.x + dest.w > *TextFont_textureWidth(f)){
            dest.y += lineSkip;
            dest.x = 0;
        }
        if(dest.y + dest.h > *TextFont_textureHeight(f)){
            GRAPHICAL_LOG_ERROR("Error while building font's atlas: No font's texture space enough to build atlas\n");
            exit(1);
        }

        //
        SDL_BlitSurface(chr_surf, NULL, s, &dest);
        glyph = &((*TextFont_glyphs(f))[j]);
        (*TextFont_glyphs(f))[j] = dest;

        SDL_FreeSurface(chr_surf);
        dest.x += dest.w;
        ++i;
        ++j;
    }

    *Texture_raw(TextFont_texture(f)) = SDL_CreateTextureFromSurface(*TextFont_renderer(f), s);
    if(!*Texture_raw(TextFont_texture(f))){
        GRAPHICAL_LOG_ERROR("Error while building font's atlas: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_FreeSurface(s);
}


void TextFont_glyphSize(TextFont*f, int glyph, int*w, int*h)
{
    Glyph g;
    int width, height;

    g = (*TextFont_glyphs(f))[glyph];
    width = g.w;
    height = g.h;

    if(w){
        *w = width;
    }
    if(h){
        *h = height;
    }
}


void TextFont_destroy(TextFont*f)
{
    SDL_DestroyTexture(*Texture_raw(TextFont_texture(f)));
}
