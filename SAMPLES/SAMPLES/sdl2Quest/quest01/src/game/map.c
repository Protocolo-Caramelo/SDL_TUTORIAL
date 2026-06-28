/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "map.h"

extern Game game;

void drawMap(AtlasImage **tiles)
{
	int x, y, mx, my;

	for (x = 0; x < MAP_RENDER_WIDTH; x++)
	{
		for (y = 0; y < MAP_RENDER_HEIGHT; y++)
		{
			mx = game.map->camera.x + x;
			my = game.map->camera.y + y;

			if (mx >= 0 && my >= 0 && mx < game.map->width && my < game.map->height)
			{
				blitAtlasImage(tiles[game.map->data[mx][my]], x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, 0, SDL_FLIP_NONE);
			}
		}
	}
}
