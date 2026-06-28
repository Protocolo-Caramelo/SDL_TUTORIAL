/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "map.h"

extern Dungeon dungeon;

static void loadTiles(void);
static void randomWalk(void);
static void tidyWalls(void);

static AtlasImage *tiles[MAX_TILES];
static AtlasImage *darkTile;

void initMap(void)
{
	loadTiles();
}

void drawMap(void)
{
	int      x, y, mx, my;
	MapTile *t;

	for (x = 0; x < MAP_RENDER_WIDTH; x++)
	{
		for (y = 0; y < MAP_RENDER_HEIGHT; y++)
		{
			mx = x + dungeon.camera.x;
			my = y + dungeon.camera.y;

			if (mx >= 0 && my >= 0 && mx < MAP_WIDTH && my < MAP_HEIGHT)
			{
				t = &dungeon.map[mx][my];

				if (t->revealed)
				{
					if (t->tile != TILE_HOLE)
					{
						blitAtlasImage(tiles[t->tile], (x * MAP_TILE_SIZE) + MAP_RENDER_X, (y * MAP_TILE_SIZE) + MAP_RENDER_Y, 0, SDL_FLIP_NONE);

						if (!t->visible)
						{
							blitAtlasImage(darkTile, (x * MAP_TILE_SIZE) + MAP_RENDER_X, (y * MAP_TILE_SIZE) + MAP_RENDER_Y, 0, SDL_FLIP_NONE);
						}
					}
				}
			}
		}
	}
}

void generateMap(void)
{
	randomWalk();

	tidyWalls();
}

static void randomWalk(void)
{
	int    x, y, dx, dy, straight, n;
	double coverage;

	coverage = 20 + rand() % 16;

	n = (MAP_WIDTH * MAP_HEIGHT) * (coverage * 0.01);

	for (x = 0; x < MAP_WIDTH; x++)
	{
		for (y = 0; y < MAP_HEIGHT; y++)
		{
			memset(&dungeon.map[x][y], 0, sizeof(MapTile));

			dungeon.map[x][y].tile = TILE_WALL + rand() % 3;
		}
	}

	x = 1 + rand() % (MAP_WIDTH - 2);
	y = 1 + rand() % (MAP_HEIGHT - 2);

	dx = dy = straight = 0;

	dungeon.map[x][y].tile = TILE_GROUND;

	while (n > 0)
	{
		straight = MAX(straight - 1, 0);

		if (straight == 0)
		{
			switch (rand() % 5)
			{
				case 0:
					dx = 0;
					dy = -1;
					break;

				case 1:
					dx = 0;
					dy = 1;
					break;

				case 2:
					dx = -1;
					dy = 0;
					break;

				case 3:
					dx = 1;
					dy = 0;
					break;

				default:
					straight = 4 + rand() % 8;
					break;
			}
		}

		x = MIN(MAX(x + dx, 1), MAP_WIDTH - 2);
		y = MIN(MAX(y + dy, 1), MAP_HEIGHT - 2);

		if (dungeon.map[x][y].tile >= TILE_WALL)
		{
			dungeon.map[x][y].tile = TILE_GROUND;

			if (rand() % 10 == 0)
			{
				dungeon.map[x][y].tile += rand() % 5;
			}

			n--;
		}
	}

	dungeon.player->x = x;
	dungeon.player->y = y;
}

static void tidyWalls(void)
{
	int x, y, tmp[MAP_WIDTH][MAP_HEIGHT], wallsRemoved;

	do
	{
		wallsRemoved = 0;

		for (x = 0; x < MAP_WIDTH; x++)
		{
			for (y = 0; y < MAP_HEIGHT; y++)
			{
				tmp[x][y] = dungeon.map[x][y].tile;
			}
		}

		for (x = 1; x < MAP_WIDTH - 1; x++)
		{
			for (y = 1; y < MAP_HEIGHT - 1; y++)
			{
				if (dungeon.map[x][y].tile >= TILE_WALL && countWalls(x, y) < 2)
				{
					wallsRemoved = 1;

					tmp[x][y] = TILE_GROUND;
				}
			}
		}

		for (x = 0; x < MAP_WIDTH; x++)
		{
			for (y = 0; y < MAP_HEIGHT; y++)
			{
				dungeon.map[x][y].tile = tmp[x][y];
			}
		}
	} while (wallsRemoved != 0);
}

int countWalls(int mx, int my)
{
	int x, y, n;

	n = 0;

	for (x = -1; x <= 1; x++)
	{
		for (y = -1; y <= 1; y++)
		{
			if ((x != 0 || y != 0) && dungeon.map[mx + x][my + y].tile >= TILE_WALL)
			{
				n++;
			}
		}
	}

	return n;
}

static void loadTiles(void)
{
	int  i;
	char filename[MAX_FILENAME_LENGTH];

	for (i = 1; i < MAX_TILES; i++)
	{
		sprintf(filename, "gfx/tiles/%d.png", i);

		tiles[i] = getAtlasImage(filename, 0);
	}

	darkTile = getAtlasImage("gfx/tiles/dark.png", 1);
}
