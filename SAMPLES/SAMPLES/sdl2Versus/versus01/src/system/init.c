/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

#include <time.h>

#include "../common.h"

#include "../game/models.h"
#include "draw.h"

static void showLoadingStep(double step, double maxSteps);

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

	app.window = SDL_CreateWindow("SDL2 Versus 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	SDL_ShowCursor(0);
}

void initGameSystem(void)
{
	int i, numInitFuns;
	void (*initFuncs[])(void) = {initDraw, initModels};

	srand(time(NULL));

	numInitFuns = sizeof(initFuncs) / sizeof(void *);

	for (i = 0; i < numInitFuns; i++)
	{
		showLoadingStep(i + 1, numInitFuns);

		initFuncs[i]();
	}
}

static void showLoadingStep(double step, double maxSteps)
{
	SDL_Rect r;

	prepareScene();

	r.w = 600;
	r.h = 6;
	r.x = (SCREEN_WIDTH - r.w) / 2;
	r.y = (SCREEN_HEIGHT - r.h) / 2;

	SDL_SetRenderDrawColor(app.renderer, 48, 48, 48, 255);
	SDL_RenderFillRect(app.renderer, &r);

	r.w *= (step / maxSteps);

	SDL_SetRenderDrawColor(app.renderer, 120, 160, 255, 255);
	SDL_RenderFillRect(app.renderer, &r);

	presentScene();

	SDL_Delay(1);
}

void cleanup(void)
{
	SDL_DestroyRenderer(app.renderer);

	SDL_DestroyWindow(app.window);

	SDL_Quit();
}
