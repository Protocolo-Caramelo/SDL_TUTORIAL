/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/util.h"

extern Stage stage;

void initEntities(void)
{
	memset(&stage.entityHead, 0, sizeof(Entity));

	stage.entityTail = &stage.entityHead;
}

void doEntities(void)
{
	Entity *e;

	for (e = stage.entityHead.next; e != NULL; e = e->next)
	{
		e->tick(e);
	}
}

void drawEntities(void)
{
	Entity *e;
	int     x, y;

	for (e = stage.entityHead.next; e != NULL; e = e->next)
	{
		x = e->x - stage.camera.x;
		y = e->y - stage.camera.y;

		if (collision(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, x, y, e->texture->rect.w, e->texture->rect.h))
		{
			e->draw(e);
		}
	}
}
