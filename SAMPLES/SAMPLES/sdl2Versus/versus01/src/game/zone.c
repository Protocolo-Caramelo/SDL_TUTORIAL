/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "entities.h"
#include "player.h"
#include "zone.h"

static void logic(void);
static void draw(void);

extern App  app;
extern Zone zone;

void initZone(void)
{
	memset(&zone, 0, sizeof(Zone));

	initEntities();

	initPlayer(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	doEntities();
}

static void draw(void)
{
	drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 24, 255);

	drawEntities();
}
