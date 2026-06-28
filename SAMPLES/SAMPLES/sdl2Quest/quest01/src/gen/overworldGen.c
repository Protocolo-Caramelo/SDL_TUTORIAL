/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "overworldGen.h"
#include "perlin.h"

extern App  app;
extern Game game;

static int generateOverworldWorker(void *p);
static void (*worldGenDone)(void);

void generateOverworld(void (*callback)(void))
{
	worldGenDone = callback;

	SDL_CreateThread(generateOverworldWorker, "generateOverworldWorker", (void *)NULL);
}

static int generateOverworldWorker(void *p)
{
	double   maxElevation, e;
	int      x, y;
	double **elevation;
	long     then;

	then = SDL_GetTicks();

	elevation = generatePerlinNoise(WORLD_WIDTH, WORLD_HEIGHT, rand());

	maxElevation = 0;

	game.overworld.map.width = WORLD_WIDTH;
	game.overworld.map.height = WORLD_HEIGHT;

	game.overworld.map.data = (int **)malloc(WORLD_WIDTH * sizeof(int *));

	for (x = 0; x < WORLD_WIDTH; x++)
	{
		game.overworld.map.data[x] = (int *)malloc(WORLD_HEIGHT * sizeof(int));

		for (y = 0; y < WORLD_HEIGHT; y++)
		{
			maxElevation = MAX(elevation[x][y], maxElevation);
		}
	}

	for (x = 0; x < WORLD_WIDTH; x++)
	{
		for (y = 0; y < WORLD_HEIGHT; y++)
		{
			e = elevation[x][y] / maxElevation;

			if (e < 0.6)
			{
				game.overworld.map.data[x][y] = MT_WATER;
			}
			else if (e < 0.61)
			{
				game.overworld.map.data[x][y] = MT_SHALLOWS;
			}
			else if (e < 0.9)
			{
				game.overworld.map.data[x][y] = MT_LAND;
			}
			else
			{
				game.overworld.map.data[x][y] = MT_MOUNTAINS;
			}
		}
	}

	freePerlin(elevation, WORLD_HEIGHT);

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Overworld generated in %ldms\n", SDL_GetTicks() - then);

	worldGenDone();

	return 0;
}
