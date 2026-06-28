/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "stars.h"

#define NUM_STARS 250

extern App app;

static Star stars[NUM_STARS];

void initStars(void)
{
	int i;

	for (i = 0; i < NUM_STARS; i++)
	{
		stars[i].x = rand() % SCREEN_WIDTH;
		stars[i].y = rand() % SCREEN_HEIGHT;
		stars[i].speed = 10 + (rand() % 50);
		stars[i].speed *= 0.1;
	}
}

void doStars(void)
{
	int i;

	for (i = 0; i < NUM_STARS; i++)
	{
		stars[i].y += (stars[i].speed * app.deltaTime);

		if (stars[i].y >= SCREEN_HEIGHT)
		{
			stars[i].y -= SCREEN_HEIGHT;
		}
	}
}

void drawStars(void)
{
	int i, c;

	for (i = 0; i < NUM_STARS; i++)
	{
		c = 50 * stars[i].speed;

		SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);

		SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x, stars[i].y - 3);
	}
}
