/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "map.h"

extern Stage stage;

static void loadTiles(void);

static AtlasImage *tiles[MAX_TILES];
static AtlasImage *routeTile;

void initMap(void)
{
	loadTiles();
}

void drawMap(void)
{
	int x, y, n;

	for (x = 0; x < MAP_WIDTH; x++)
	{
		for (y = 0; y < MAP_HEIGHT; y++)
		{
			n = stage.map[x][y].tile;

			blitAtlasImage(tiles[n], x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, 0, SDL_FLIP_NONE);
		}
	}
}

int isInsideMap(int x, int y)
{
	return x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT;
}

int isGround(int x, int y)
{
	return isInsideMap(x, y) && stage.map[x][y].tile >= TILE_GROUND && stage.map[x][y].tile < TILE_SLIME;
}

void drawAStarPath(void)
{
	int   x, y;
	Node *n;

	for (n = stage.routeHead.next; n != NULL; n = n->next)
	{
		x = MAP_TO_SCREEN(n->x);
		y = MAP_TO_SCREEN(n->y);

		blitAtlasImage(routeTile, x, y, 1, SDL_FLIP_NONE);
	}
}

static void loadTiles(void)
{
	int  i;
	char filename[MAX_FILENAME_LENGTH];

	for (i = 0; i < MAX_TILES; i++)
	{
		sprintf(filename, "gfx/tiles/%d.png", i);

		tiles[i] = getAtlasImage(filename, 0);
	}

	routeTile = getAtlasImage("gfx/tiles/route.png", 1);
}
