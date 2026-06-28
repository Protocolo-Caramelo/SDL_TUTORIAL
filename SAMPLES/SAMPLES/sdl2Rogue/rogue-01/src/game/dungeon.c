/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/entities.h"
#include "../game/entityFactory.h"
#include "../game/fogOfWar.h"
#include "../game/map.h"
#include "../game/player.h"
#include "dungeon.h"

extern App     app;
extern Dungeon dungeon;

static void logic(void);
static void draw(void);
static void createDungeon(void);
static void doCamera(void);

void initDungeon(void)
{
	memset(&dungeon, 0, sizeof(Dungeon));

	initMap();

	createDungeon();

	app.delegate.logic = logic;

	app.delegate.draw = draw;
}

static void createDungeon(void)
{
	initEntities();

	initEntity("Player");

	generateMap();

	updateFogOfWar();
}

static void logic(void)
{
	doPlayer();

	doCamera();
}

static void doCamera(void)
{
	dungeon.camera.x = dungeon.player->x - MAP_RENDER_WIDTH / 2;
	dungeon.camera.y = dungeon.player->y - MAP_RENDER_HEIGHT / 2;
}

static void draw(void)
{
	drawMap();

	drawEntities();
}
