/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "util.h"

unsigned long hashcode(const char *str)
{
	unsigned long hash = 5381;
	int           c;

	c = *str;

	while (c)
	{
		hash = ((hash << 5) + hash) + c;

		c = *str++;
	}

	hash = ((hash << 5) + hash);

	return hash;
}

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

int getDistance(int x1, int y1, int x2, int y2)
{
	int x, y;

	x = x2 - x1;
	y = y2 - y1;

	return sqrt(x * x + y * y);
}

char *readFile(char *filename)
{
	char *buffer;
	long  length;
	FILE *file;

	file = fopen(filename, "rb");

	if (file == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "No such file '%s'", filename);
		exit(1);
	}

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Reading file '%s' ...", filename);

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer = malloc(length + 1);
	memset(buffer, 0, length + 1);
	fread(buffer, 1, length, file);

	fclose(file);

	return buffer;
}
