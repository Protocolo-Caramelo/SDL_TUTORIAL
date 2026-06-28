/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "iso.h"

#define ISO_RENDER_SPEED 15
#define MAX_ISO_OBJECTS  1024

extern App app;

static int drawComparator(const void *a, const void *b);

static int       numISOObjects;
static ISOObject isoObjects[MAX_ISO_OBJECTS];
static double    drawTimer;

void initISORender(void)
{
	drawTimer = 0;
}

void doISOObjects(void)
{
	drawTimer = MIN(drawTimer + ISO_RENDER_SPEED * app.deltaTime, numISOObjects);

	// uncomment the line below to draw the scene instantly each time
	// drawTimer = numISOObjects;
}

void drawISOObjects(void)
{
	int        i;
	ISOObject *o;

	qsort(isoObjects, numISOObjects, sizeof(ISOObject), drawComparator);

	for (i = 0; i < numISOObjects; i++)
	{
		if (drawTimer >= i)
		{
			o = &isoObjects[i];

			blitAtlasImage(o->texture, o->sx, o->sy, 0, SDL_FLIP_NONE);
		}
	}
}

void clearISOObjects(void)
{
	memset(&isoObjects, 0, sizeof(ISOObject) * numISOObjects);

	numISOObjects = 0;
}

void toISO(int x, int z, int *sx, int *sy)
{
	*sx = MAP_RENDER_OFFSET_X + ((x * TILE_WIDTH / 2) + (z * TILE_WIDTH / 2));
	*sy = MAP_RENDER_OFFSET_Y + ((z * TILE_HEIGHT / 2) - (x * TILE_HEIGHT / 2));
}

void addISOObject(int x, int z, int sx, int sy, AtlasImage *texture)
{
	ISOObject *o;

	if (numISOObjects < MAX_ISO_OBJECTS)
	{
		o = &isoObjects[numISOObjects++];

		toISO(x, z, &o->x, &o->y);

		o->sx = o->x + sx;
		o->sy = o->y + sy;
		o->texture = texture;
	}
}

static int drawComparator(const void *a, const void *b)
{
	ISOObject *o1, *o2;

	o1 = (ISOObject *)a;
	o2 = (ISOObject *)b;

	return o1->y - o2->y;
}
