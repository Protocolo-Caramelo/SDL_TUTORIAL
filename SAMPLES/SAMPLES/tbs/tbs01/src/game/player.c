/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/aStar.h"
#include "../game/entityFactory.h"
#include "../game/map.h"
#include "player.h"

#define NUM_PLAYER_UNITS 1

extern App   app;
extern Stage stage;

static void doMoveUnit(void);
static void addPlayerUnits(void);

static Entity *units[NUM_PLAYER_UNITS];

void initPlayer(void)
{
	addPlayerUnits();
}

void doPlayer(void)
{
	doMoveUnit();
}

static void doMoveUnit(void)
{
	if (app.mouse.buttons[SDL_BUTTON_LEFT])
	{
		app.mouse.buttons[SDL_BUTTON_LEFT] = 0;

		createAStarRoute(stage.currentEntity, stage.selectedTile.x, stage.selectedTile.y);
	}
}

static void addPlayerUnits(void)
{
	Entity *e;
	int     i;
	char   *names[] = {"Andy"};

	for (i = 0; i < NUM_PLAYER_UNITS; i++)
	{
		e = initEntity(names[i]);

		e->side = SIDE_PLAYER;

		do
		{
			e->x = rand() % MAP_WIDTH;
			e->y = rand() % MAP_HEIGHT;
		} while (!isGround(e->x, e->y));

		units[i] = e;
	}

	stage.currentEntity = units[0];
}
