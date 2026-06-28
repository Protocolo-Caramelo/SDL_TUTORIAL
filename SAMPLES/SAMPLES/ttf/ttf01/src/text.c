/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include <SDL2/SDL_ttf.h>

#include "common.h"

#include "text.h"
#include "textures.h"

#define FONT_SIZE 48

static TTF_Font *font;
static SDL_Color white = {255, 255, 255, 255};

void initFonts(void)
{
	font = TTF_OpenFont("font/EnterCommand.ttf", FONT_SIZE);
}

SDL_Texture *getTextTexture(char *text)
{
	SDL_Surface *surface;

	surface = TTF_RenderUTF8_Blended(font, text, white);

	return toTexture(surface, 1);
}
