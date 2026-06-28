/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

#include "../common.h"

extern App  app;
extern Game game;

static double moveTimer = 0;

void doCamera(void)
{
	moveTimer = MAX(moveTimer - app.deltaTime, 0);

	if (moveTimer == 0)
	{
		if (app.keyboard[SDL_SCANCODE_A])
		{
			game.map->camera.x--;
		}

		if (app.keyboard[SDL_SCANCODE_D])
		{
			game.map->camera.x++;
		}

		if (app.keyboard[SDL_SCANCODE_W])
		{
			game.map->camera.y--;
		}

		if (app.keyboard[SDL_SCANCODE_S])
		{
			game.map->camera.y++;
		}

		moveTimer = 3;
	}

	game.map->camera.x = MIN(MAX(game.map->camera.x, 0), game.map->width - MAP_RENDER_WIDTH);
	game.map->camera.y = MIN(MAX(game.map->camera.y, 0), game.map->height - MAP_RENDER_HEIGHT);
}
