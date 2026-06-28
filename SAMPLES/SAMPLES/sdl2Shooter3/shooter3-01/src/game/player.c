/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "controls.h"
#include "effects.h"
#include "fighters.h"
#include "player.h"

#define FIGHTER_SPEED     0.5
#define MAX_FIGHTER_SPEED 16

extern App   app;
extern Stage stage;

static void tick(Entity *self);
static void draw(Entity *self);
static void doPlayerControls(Entity *self, Fighter *f);

void initPlayer(Entity *e)
{
	Fighter *f;

	f = malloc(sizeof(Fighter));
	memset(f, 0, sizeof(Fighter));

	e->facing = FACING_RIGHT;
	e->data = f;
	e->texture = getAtlasImage("gfx/fighters/kit-e.png", 1);

	e->tick = tick;
	e->draw = draw;

	stage.player = e;
}

static void tick(Entity *self)
{
	Fighter *f;

	f = (Fighter *)self->data;

	doPlayerControls(self, f);

	fighterTick(self, f);

	stage.ssx = -f->dx;
	stage.ssy = -f->dy;

	if (stage.engineEffectTimer <= 0)
	{
		addEngineEffect(self->x + (self->facing == FACING_LEFT ? self->texture->rect.w : 0), self->y + 18);
	}
}

static void doPlayerControls(Entity *self, Fighter *f)
{
	if (isControl(CONTROL_LEFT))
	{
		f->dx -= FIGHTER_SPEED * app.deltaTime;

		self->facing = FACING_LEFT;
	}

	if (isControl(CONTROL_RIGHT))
	{
		f->dx += FIGHTER_SPEED * app.deltaTime;

		self->facing = FACING_RIGHT;
	}

	if (isControl(CONTROL_UP))
	{
		f->dy -= FIGHTER_SPEED * app.deltaTime;
	}

	if (isControl(CONTROL_DOWN))
	{
		f->dy += FIGHTER_SPEED * app.deltaTime;
	}

	f->dx = MIN(MAX(f->dx, -MAX_FIGHTER_SPEED), MAX_FIGHTER_SPEED);
	f->dy = MIN(MAX(f->dy, -MAX_FIGHTER_SPEED), MAX_FIGHTER_SPEED);
}

static void draw(Entity *self)
{
	Fighter *f;

	f = (Fighter *)self->data;

	fighterDraw(self, f);
}
