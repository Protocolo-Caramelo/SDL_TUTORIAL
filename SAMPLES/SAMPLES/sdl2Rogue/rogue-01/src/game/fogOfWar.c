/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/util.h"
#include "fogOfWar.h"

#define VIS_DISTANCE 16

extern Dungeon dungeon;
extern Entity *player;

void updateFogOfWar(void)
{
	int x, y, mx, my;

	for (x = 0; x < MAP_WIDTH; x++)
	{
		for (y = 0; y < MAP_HEIGHT; y++)
		{
			dungeon.map[x][y].visible = 0;
		}
	}

	for (y = -VIS_DISTANCE; y <= VIS_DISTANCE; y++)
	{
		for (x = -VIS_DISTANCE; x <= VIS_DISTANCE; x++)
		{
			mx = dungeon.player->x + x;
			my = dungeon.player->y + y;

			if (getDistance(dungeon.player->x, dungeon.player->y, mx, my) <= VIS_DISTANCE)
			{
				if (mx >= 0 && my >= 0 && mx < MAP_WIDTH && my < MAP_HEIGHT)
				{
					if (!dungeon.map[mx][my].visible && hasLOS(dungeon.player, mx, my))
					{
						dungeon.map[mx][my].revealed = dungeon.map[mx][my].visible = 1;
					}
				}
			}
		}
	}
}

int hasLOS(Entity *src, int x2, int y2)
{
	int x1, y1, dx, dy, sx, sy, err, e2;

	x1 = src->x;
	y1 = src->y;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx - dy;

	while (1)
	{
		e2 = 2 * err;

		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}

		if (x1 == x2 && y1 == y2)
		{
			return 1;
		}

		if (dungeon.map[x1][y1].tile >= TILE_WALL)
		{
			return 0;
		}
	}

	return 0;
}
