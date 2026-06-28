/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/util.h"
#include "camera.h"
#include "map.h"
#include "overworld.h"
#include "questLog.h"

#define NUM_TILES (MT_MAX * TILE_TYPE_RANGE)

extern App  app;
extern Game game;

static void logic(void);
static void draw(void);
static void loadMapTiles(void);
static void decorate(void);

static AtlasImage *tiles[NUM_TILES];
static int         doDecorate;

void initOverworld(void)
{
	game.overworld.seed = rand();

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Generating world #%ld", game.overworld.seed);

	srand(game.overworld.seed);

	game.map = &game.overworld.map;
	game.map->camera.x = (WORLD_WIDTH - MAP_RENDER_WIDTH) / 2;
	game.map->camera.y = (WORLD_HEIGHT - MAP_RENDER_HEIGHT) / 2;

	loadMapTiles();

	doDecorate = 1;
}

void enterOverworld(void)
{
	if (doDecorate)
	{
		doDecorate = 0;

		decorate();
	}

	game.map = &game.overworld.map;

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	if (app.keyboard[SDL_SCANCODE_TAB])
	{
		openQuestLog(&enterOverworld);

		app.transitionTimer = FPS / 4;

		app.keyboard[SDL_SCANCODE_TAB] = 0;
	}

	doCamera();
}

static void draw(void)
{
	drawMap(tiles);
}

static void loadMapTiles(void)
{
	int i;

	for (i = 0; i < NUM_TILES; i++)
	{
		tiles[i] = getAtlasImage(expiringFormattedString("gfx/tiles/overworld/%d.png", i), 0);
	}
}

static void decorate(void)
{
	int x, y, n;

	for (x = 0; x < WORLD_WIDTH; x++)
	{
		for (y = 0; y < WORLD_HEIGHT; y++)
		{
			game.map->data[x][y] *= TILE_TYPE_RANGE;

			n = game.map->data[x][y] + rand() % TILE_TYPE_RANGE;

			if (tiles[n] != NULL)
			{
				game.map->data[x][y] = n;
			}
		}
	}
}
