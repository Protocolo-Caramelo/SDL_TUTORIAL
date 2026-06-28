/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "entities.h"

extern App   app;
extern Stage stage;

static AtlasImage *selectedUnitTexture;
static double      selectedUnitPulse;

void initEntities(void)
{
	memset(&stage.entityHead, 0, sizeof(Entity));
	stage.entityTail = &stage.entityHead;

	selectedUnitTexture = getAtlasImage("gfx/hud/selectedUnit.png", 1);

	selectedUnitPulse = 0;
}

void doEntities(void)
{
	selectedUnitPulse += 0.1 * app.deltaTime;
}

void drawEntities(void)
{
	Entity *e;
	int     x, y, size;

	for (e = stage.entityHead.next; e != NULL; e = e->next)
	{
		e->draw(e);
	}

	if (!stage.animating)
	{
		size = 48 + sin(selectedUnitPulse) * 8;

		x = MAP_TO_SCREEN(stage.currentEntity->x);
		y = MAP_TO_SCREEN(stage.currentEntity->y);

		blitScaled(selectedUnitTexture, x, y, size, size, 1);
	}
}
