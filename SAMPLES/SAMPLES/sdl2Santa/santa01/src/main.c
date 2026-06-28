/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "game/stage.h"
#include "main.h"
#include "system/draw.h"
#include "system/init.h"
#include "system/input.h"

static void logic(void);

App   app;
Stage stage;

int main(int argc, char *argv[])
{
	long then;

	memset(&app, 0, sizeof(App));

	initSDL();

	initGameSystem();

	initStage();

	atexit(cleanup);

	while (1)
	{
		then = SDL_GetTicks();

		prepareScene();

		doInput();

		logic();

		app.delegate.draw();

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
