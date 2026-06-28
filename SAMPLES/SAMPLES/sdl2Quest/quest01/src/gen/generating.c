/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/overworld.h"
#include "../game/questLog.h"
#include "../system/draw.h"
#include "../system/util.h"
#include "overworldGen.h"

extern App  app;
extern Game game;

static void generateOverworldDone(void);
static void logic(void);
static void draw(void);
static void drawProgressBar(void);

static double loading;
static int    done;
static long   startTime;

void generateWorld(void)
{
	loading = 0;

	done = 0;

	startTime = SDL_GetTicks();

	initOverworld();

	generateOverworld(generateOverworldDone);

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void generateOverworldDone(void)
{
	done = 1;
}

static void logic(void)
{
	loading += (0.4 * app.deltaTime);

	if (done)
	{
		game.map = &game.overworld.map;

		initQuestLog();

		enterOverworld();

		app.transitionTimer = FPS / 2;

		app.expireStrings = 1;
	}
}

static void draw(void)
{
	drawProgressBar();
}

static void drawProgressBar(void)
{
	int i, w, g, b, l, n, m, v, s;

	n = 20;
	m = 20;
	v = 5;
	s = 15;

	w = (SCREEN_WIDTH - (m * n)) / 2;

	l = (int)loading % (n + v + 1);

	for (i = 0; i < n; i++)
	{
		g = 200;
		b = 255;

		if (i > l || i < l - v)
		{
			g /= 3;
			b /= 3;
		}

		drawRect(w + (i * m), SCREEN_HEIGHT - 150, s, s, 0, g, b, 255);
	}
}
