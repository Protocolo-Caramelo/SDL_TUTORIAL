/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "textures.h"

extern App app;

SDL_Texture *toTexture(SDL_Surface *surface, int destroySurface)
{
	SDL_Texture *texture;

	texture = SDL_CreateTextureFromSurface(app.renderer, surface);

	if (destroySurface)
	{
		SDL_FreeSurface(surface);
	}

	return texture;
}
