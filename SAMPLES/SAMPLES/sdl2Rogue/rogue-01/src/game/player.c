/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/entities.h"
#include "../game/fogOfWar.h"
#include "../system/atlas.h"
#include "player.h"

#define MOVE_DELAY 5

extern App     app;
extern Dungeon dungeon;

static double moveDelay;

void initPlayer(Entity *e)
{
	STRCPY(e->name, "Player");
	e->type = ET_PLAYER;
	e->texture = getAtlasImage("gfx/entities/girl.png", 1);

	dungeon.player = e;

	moveDelay = 0;
}

void doPlayer(void)
{
	int dx, dy;

	moveDelay = MAX(moveDelay - app.deltaTime, 0);

	if (moveDelay == 0)
	{
		dx = dy = 0;

		if (app.keyboard[SDL_SCANCODE_W])
		{
			dy = -1;
		}

		if (app.keyboard[SDL_SCANCODE_S])
		{
			dy = 1;
		}

		if (app.keyboard[SDL_SCANCODE_A])
		{
			dx = -1;
		}

		if (app.keyboard[SDL_SCANCODE_D])
		{
			dx = 1;
		}

		if (dx != 0 || dy != 0)
		{
			moveEntity(dungeon.player, dx, dy);

			moveDelay = MOVE_DELAY;

			updateFogOfWar();
		}
	}
}
