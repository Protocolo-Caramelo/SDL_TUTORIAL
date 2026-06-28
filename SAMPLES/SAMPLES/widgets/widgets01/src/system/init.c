/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../common.h"

#include "../system/text.h"
#include "../system/widgets.h"
#include "init.h"

extern App app;

void initSDL(void)
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow("SDL2 Widgets 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_ShowCursor(0);
}

void initGameSystem(void)
{
	initFonts();

	initWidgets();
}

void cleanup(void)
{
	IMG_Quit();

	TTF_Quit();

	SDL_DestroyRenderer(app.renderer);

	SDL_DestroyWindow(app.window);

	SDL_Quit();
}
