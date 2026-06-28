/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#define MAX_STAR_SPEED 3

static Star   stars[MAX_STARS];
static double dx, dy;

extern App app;

void initStarfield(void)
{
	int   i;
	Star *s;

	for (i = 0; i < MAX_STARS; i++)
	{
		s = &stars[i];

		s->x = rand() % SCREEN_WIDTH;
		s->y = rand() % SCREEN_HEIGHT;
		s->speed = rand() % (MAX_STAR_SPEED * 10);
		s->speed *= 0.1;

		s->speed = MAX(s->speed, 1);
	}
}

void doStarfield(double _dx, double _dy)
{
	int   i;
	Star *s;

	dx = _dx;
	dy = _dy;

	for (i = 0; i < MAX_STARS; i++)
	{
		s = &stars[i];

		s->x += dx * s->speed * app.deltaTime;
		s->y += dy * s->speed * app.deltaTime;

		if (s->x < 0)
		{
			s->x = SCREEN_WIDTH;
		}

		if (s->y < 0)
		{
			s->y = SCREEN_HEIGHT;
		}

		if (s->x > SCREEN_WIDTH)
		{
			s->x = 0;
		}

		if (s->y > SCREEN_HEIGHT)
		{
			s->y = 0;
		}
	}
}

void drawStarfield(void)
{
	int   i, c;
	Star *s;

	for (i = 0; i < MAX_STARS; i++)
	{
		s = &stars[i];

		c = (200.0 / MAX_STAR_SPEED) * s->speed;

		SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);

		SDL_RenderDrawLine(app.renderer, s->x, s->y, s->x - dx, s->y - dy);
	}
}
