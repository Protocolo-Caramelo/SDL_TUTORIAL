/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "game/zone.h"
#include "main.h"
#include "system/draw.h"
#include "system/init.h"
#include "system/input.h"

static void logic(void);

App  app;
Zone zone;

int main(int argc, char *argv[])
{
	long then;

	memset(&app, 0, sizeof(App));

	initSDL();

	initGameSystem();

	atexit(cleanup);

	initZone();

	while (1)
	{
		then = SDL_GetTicks();

		prepareScene();

		doInput();

		app.transitionTimer = MAX(app.transitionTimer - app.deltaTime, 0);

		if (app.transitionTimer == 0)
		{
			logic();

			if (app.transitionTimer == 0)
			{
				app.delegate.draw();
			}
		}

		presentScene();

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
