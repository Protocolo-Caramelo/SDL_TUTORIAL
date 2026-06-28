/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/aStar.h"
#include "../game/map.h"
#include "../system/draw.h"
#include "units.h"

extern App   app;
extern Stage stage;

static void move(void);
static void draw(Entity *e);

static double moveTimer;

void initUnits(void)
{
	moveTimer = 0;
}

void initUnit(Entity *e)
{
	e->draw = draw;
}

void doUnits(void)
{
	if (stage.routeHead.next != NULL)
	{
		move();
	}
}

static void move(void)
{
	Node *n;

	moveTimer -= app.deltaTime;

	if (moveTimer <= 0)
	{
		n = stage.routeHead.next;

		if (n->x < stage.currentEntity->x)
		{
			stage.currentEntity->facing = FACING_LEFT;
		}
		else if (n->x > stage.currentEntity->x)
		{
			stage.currentEntity->facing = FACING_RIGHT;
		}

		stage.currentEntity->x = n->x;
		stage.currentEntity->y = n->y;

		stage.routeHead.next = n->next;

		free(n);

		if (stage.routeHead.next == NULL)
		{
			resetAStar();
		}

		moveTimer = 5;
	}
}

static void draw(Entity *self)
{
	int x, y;

	x = MAP_TO_SCREEN(self->x);
	y = MAP_TO_SCREEN(self->y);

	blitAtlasImage(self->texture, x, y, 1, self->facing == FACING_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

int isBlocked(int x, int y)
{
	if (!isGround(x, y))
	{
		return 1;
	}

	return 0;
}
