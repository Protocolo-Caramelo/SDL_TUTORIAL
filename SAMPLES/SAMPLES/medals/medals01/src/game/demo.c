/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/medals.h"
#include "../system/text.h"
#include "demo.h"

extern App  app;
extern Game game;

static void logic(void);
static void draw(void);

static int spaceCount;

void initDemo(void)
{
	spaceCount = 0;

	app.delegate.logic = logic;

	app.delegate.draw = draw;
}

static void logic(void)
{
	if (app.keyboard[SDL_SCANCODE_1])
	{
		app.keyboard[SDL_SCANCODE_1] = 0;

		awardMedal("key1");
	}

	if (app.keyboard[SDL_SCANCODE_RETURN])
	{
		app.keyboard[SDL_SCANCODE_RETURN] = 0;

		awardMedal("keyReturn");
	}

	if (app.keyboard[SDL_SCANCODE_SPACE])
	{
		app.keyboard[SDL_SCANCODE_SPACE] = 0;

		if (++spaceCount >= 3)
		{
			awardMedal("keySpace");
		}
	}
}

static void draw(void)
{
	Medal *m;
	int    y, r, g, b;

	y = 200;

	for (m = game.medalsHead.next; m != NULL; m = m->next)
	{
		r = g = b = 128;

		if (m->awardDate > 0)
		{
			r = g = 255;
			b = 0;
		}

		drawText(m->title, 200, y, r, g, b, TEXT_ALIGN_LEFT, 0);

		drawText(m->description, 240, y + 45, r, g, b, TEXT_ALIGN_LEFT, 0);

		y += 135;
	}
}
