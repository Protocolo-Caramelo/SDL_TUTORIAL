/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "gen/generating.h"
#include "main.h"
#include "system/draw.h"
#include "system/init.h"
#include "system/input.h"
#include "system/util.h"

App  app;
Game game;

static void logic(void);
static void doFPS(void);
static void doTransition(void);

static int  fps;
static long nextFPS;

int main(int argc, char *argv[])
{
	long then;

	memset(&app, 0, sizeof(App));

	initSDL();

	atexit(cleanup);

	memset(&game, 0, sizeof(Game));

	initGameSystem();

	generateWorld();

	nextFPS = SDL_GetTicks() + 1000;

	while (1)
	{
		then = SDL_GetTicks();

		prepareScene();

		doInput();

		doTransition();

		if (app.transitionTimer == 0)
		{
			logic();

			if (app.transitionTimer == 0)
			{
				app.delegate.draw();
			}
		}

		presentScene();

		if (app.expireStrings)
		{
			expireStrings();
		}

		/* allow the CPU/GPU to breathe */
		SDL_Delay(1);

		app.deltaTime = LOGIC_RATE * (SDL_GetTicks() - then);

		doFPS();
	}

	return 0;
}

static void doTransition(void)
{
	app.transitionTimer = MAX(app.transitionTimer - app.deltaTime, 0);

	if (app.transitionTimer > 0)
	{
		clearInput();
	}
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

		game.time++;
	}

	app.delegate.logic();

	game.time += app.deltaTime;
}

static void doFPS(void)
{
	fps++;

	if (SDL_GetTicks() >= nextFPS)
	{
		app.dev.fps = fps;

		fps = 0;

		nextFPS = SDL_GetTicks() + 1000;
	}
}
