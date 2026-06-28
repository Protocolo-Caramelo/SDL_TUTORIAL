/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "entities.h"
#include "models.h"
#include "player.h"

static void tick(Entity *self);
static void draw(Entity *self);

extern App app;

void initPlayer(int x, int y)
{
	Entity *e;

	e = spawnEntity(ET_PLAYER);
	e->position.x = x;
	e->position.y = y;
	e->model = loadModel("data/models/player1");

	e->tick = tick;
	e->draw = draw;
}

static void tick(Entity *self)
{
	self->angle += app.deltaTime;
}

static void draw(Entity *self)
{
	drawModel(self->model, self->position, self->angle);
}
