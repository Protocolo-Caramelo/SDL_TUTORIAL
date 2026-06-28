/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/units.h"
#include "../system/atlas.h"
#include "mages.h"

void initMage(Entity *e, char *filename)
{
	e->type = ET_MAGE;
	e->solid = 1;
	e->texture = getAtlasImage(filename, 1);

	initUnit(e);
}

void initAndyMage(Entity *e)
{
	STRCPY(e->name, "Andy");

	initMage(e, "gfx/units/andy.png");
}
