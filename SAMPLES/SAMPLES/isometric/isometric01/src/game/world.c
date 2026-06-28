/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/iso.h"
#include "../game/map.h"
#include "world.h"

extern App   app;
extern World world;

static void logic(void);
static void draw(void);

void initWorld(void)
{
	initMap();

	initISORender();

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	doISOObjects();
}

static void draw(void)
{
	clearISOObjects();

	drawMap();

	drawISOObjects();
}
