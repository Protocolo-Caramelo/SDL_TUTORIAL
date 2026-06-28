/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "map.h"
#include "stage.h"

extern App app;

static void logic(void);
static void draw(void);

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	initMap();
}

static void logic(void)
{
}

static void draw(void)
{
	SDL_SetRenderDrawColor(app.renderer, 128, 192, 255, 255);
	SDL_RenderFillRect(app.renderer, NULL);

	drawMap();
}
