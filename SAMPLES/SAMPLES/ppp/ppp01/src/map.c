/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "draw.h"
#include "io.h"
#include "map.h"
#include "textures.h"

extern Stage stage;

static void loadTiles(void);
static void loadMap(const char *filename);

static SDL_Texture *tiles[MAX_TILES];

void initMap(void)
{
	memset(&stage.map, 0, sizeof(int) * MAP_WIDTH * MAP_HEIGHT);

	loadTiles();

	loadMap("data/map01.dat");
}

void drawMap(void)
{
	int x, y, n;

	for (y = 0; y < MAP_RENDER_HEIGHT; y++)
	{
		for (x = 0; x < MAP_RENDER_WIDTH; x++)
		{
			n = stage.map[x][y];

			if (n > 0)
			{
				blit(tiles[n], x * TILE_SIZE, y * TILE_SIZE, 0);
			}
		}
	}
}

static void loadTiles(void)
{
	int  i;
	char filename[MAX_FILENAME_LENGTH];

	for (i = 1; i < MAX_TILES; i++)
	{
		sprintf(filename, "gfx/tile%d.png", i);

		tiles[i] = loadTexture(filename);
	}
}

static void loadMap(const char *filename)
{
	char *data, *p;
	int   x, y;

	data = readFile(filename);

	p = data;

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			sscanf(p, "%d", &stage.map[x][y]);

			do
			{
				p++;
			} while (*p != ' ' && *p != '\n');
		}
	}

	free(data);
}
