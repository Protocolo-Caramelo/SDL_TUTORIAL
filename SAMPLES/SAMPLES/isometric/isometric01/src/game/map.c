/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/iso.h"
#include "../system/atlas.h"
#include "map.h"

#define MAX_TILES 50

extern World world;

static void loadTiles(void);

static AtlasImage *tiles[MAX_TILES];

void initMap(void)
{
	int x, z;

	for (x = 0; x < MAP_RENDER_SIZE; x++)
	{
		for (z = 0; z < MAP_RENDER_SIZE; z++)
		{
			if (x > 14 && x < 20)
			{
				world.map[x][z].tile = rand() % 3;
			}
			else
			{
				world.map[x][z].tile = 10 + rand() % 3;
			}
		}
	}

	loadTiles();
}

void drawMap(void)
{
	int x, z, n;

	for (x = 0; x < MAP_RENDER_SIZE; x++)
	{
		for (z = 0; z < MAP_RENDER_SIZE; z++)
		{
			n = world.map[x][z].tile;

			if (n >= 0)
			{
				addISOObject(x, z, 0, 0, tiles[n]);
			}
		}
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
}
