/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "game/world.h"
#include "main.h"
#include "system/draw.h"
#include "system/init.h"
#include "system/input.h"

App   app;
World world;

static void logic(void);

int main(int argc, char *argv[])
{
	long then, nextSecond;
	int  frames;

	memset(&app, 0, sizeof(App));

	initSDL();

	initGameSystem();

	initWorld();

	atexit(cleanup);

	frames = 0;

	nextSecond = SDL_GetTicks() + 1000;

	while (1)
	{
		then = SDL_GetTicks();

		prepareScene();

		doInput();

		logic();

		app.delegate.draw();

		presentScene();

		frames++;

		if (SDL_GetTicks() >= nextSecond)
		{
			app.dev.fps = frames;

			nextSecond = SDL_GetTicks() + 1000;

			frames = 0;
		}

		/* allow the CPU/GPU to breathe */
		SDL_Delay(1);

		app.deltaTime = LOGIC_RATE * (SDL_GetTicks() - then);
	}

	return 0;
}

static void logic(void)
{
	double tmpDelta;

	/* don't exceed target logic rate */
	while (app.deltaTime > 1)
	{
		tmpDelta = app.deltaTime;

		app.deltaTime = 1;

		app.delegate.logic();

		app.deltaTime = (tmpDelta - 1);
	}

	app.delegate.logic();
}
