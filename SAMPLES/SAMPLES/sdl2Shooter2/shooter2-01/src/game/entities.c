/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "entities.h"

extern Stage stage;

void initEntities(void)
{
	memset(&stage.entityHead, 0, sizeof(Entity));
	stage.entityTail = &stage.entityHead;
}

Entity *spawnEntity(void)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));

	stage.entityTail->next = e;
	stage.entityTail = e;

	return e;
}

void drawEntities(void)
{
	Entity *e;

	for (e = stage.entityHead.next; e != NULL; e = e->next)
	{
		blitAtlasImage(e->texture, e->x, e->y, 0, SDL_FLIP_NONE);
	}
}
