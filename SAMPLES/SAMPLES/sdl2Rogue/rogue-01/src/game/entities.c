/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "entities.h"

extern Dungeon dungeon;

void initEntities(void)
{
	dungeon.entityTail = &dungeon.entityHead;
}

void moveEntity(Entity *e, int dx, int dy)
{
	int x, y;

	x = e->x + dx;
	y = e->y + dy;

	if (dx < 0)
	{
		e->facing = FACING_LEFT;
	}
	else if (dx > 0)
	{
		e->facing = FACING_RIGHT;
	}

	if (x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT && dungeon.map[x][y].tile >= TILE_GROUND && dungeon.map[x][y].tile < TILE_WALL)
	{
		e->x = x;
		e->y = y;
	}
}

void drawEntities(void)
{
	Entity *e;
	int     x, y;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		x = (e->x - dungeon.camera.x) * MAP_TILE_SIZE;
		y = (e->y - dungeon.camera.y) * MAP_TILE_SIZE;

		blitAtlasImage(e->texture, x + MAP_RENDER_X, y + MAP_RENDER_Y, 0, e->facing == FACING_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	}
}
