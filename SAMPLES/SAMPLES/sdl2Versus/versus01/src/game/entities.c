/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "entities.h"

extern Zone zone;

void initEntities(void)
{
	memset(&zone.entityHead, 0, sizeof(Entity));
	zone.entityTail = &zone.entityHead;
}

void doEntities(void)
{
	Entity *e;

	for (e = zone.entityHead.next; e != NULL; e = e->next)
	{
		e->tick(e);
	}
}

void drawEntities(void)
{
	Entity *e;

	for (e = zone.entityHead.next; e != NULL; e = e->next)
	{
		e->draw(e);
	}
}

Entity *spawnEntity(int type)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));

	e->type = type;

	zone.entityTail->next = e;
	zone.entityTail = e;

	return e;
}
