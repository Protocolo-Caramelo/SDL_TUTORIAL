/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "fighters.h"

extern App   app;
extern Stage stage;

void fighterTick(Entity *e, Fighter *f)
{
	e->x += f->dx * app.deltaTime;
	e->y += f->dy * app.deltaTime;
}

void fighterDraw(Entity *e, Fighter *f)
{
	int x, y;

	x = e->x - stage.camera.x;
	y = e->y - stage.camera.y;

	blitAtlasImage(e->texture, x, y, 0, e->facing == FACING_LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
