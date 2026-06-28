/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "mapGen.h"

extern Stage stage;

static void decorate(void);

void generateMap(void)
{
	int x, y;

	for (x = 0; x < MAP_WIDTH; x++)
	{
		for (y = 0; y < MAP_HEIGHT; y++)
		{
			stage.map[x][y].tile = TILE_GROUND;

			if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1)
			{
				stage.map[x][y].tile = TILE_WALL;
			}
		}
	}

	decorate();
}

static void decorate(void)
{
	int x, y;

	for (x = 0; x < MAP_WIDTH; x++)
	{
		for (y = 0; y < MAP_HEIGHT; y++)
		{
			if (stage.map[x][y].tile == 0 && y < (MAP_HEIGHT - 1) && stage.map[x][y + 1].tile != 0)
			{
				stage.map[x][y].tile = 1;
			}

			if (stage.map[x][y].tile == TILE_GROUND && x > 0 && stage.map[x - 1][y].tile < TILE_GROUND)
			{
				stage.map[x][y].tile = 6;
			}
		}
	}
}
