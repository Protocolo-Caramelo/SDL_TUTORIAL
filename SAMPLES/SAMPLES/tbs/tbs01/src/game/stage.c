/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/entities.h"
#include "../game/hud.h"
#include "../game/map.h"
#include "../game/mapGen.h"
#include "../game/player.h"
#include "../game/units.h"
#include "stage.h"

extern App   app;
extern Stage stage;

static void logic(void);
static void draw(void);

void initStage(void)
{
	memset(&stage, 0, sizeof(Stage));

	initEntities();

	initUnits();

	initHud();

	initMap();

	generateMap();

	initPlayer();

	app.delegate.logic = logic;

	app.delegate.draw = draw;
}

static void logic(void)
{
	if (!stage.animating)
	{
		doPlayer();
	}

	doEntities();

	doUnits();

	doHud();

	stage.animating = stage.routeHead.next != NULL;

	app.mouse.visible = !stage.animating;
}

static void draw(void)
{
	drawMap();

	drawAStarPath();

	drawEntities();

	drawHud();
}
