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

double getAngle(int x1, int y1, int x2, int y2)
{
	double angle;

	angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);

	if (angle >= 0)
	{
		return (int)angle % 360;
	}

	return (int)(angle + 360) % 360;
}

void calcSlope(int x1, int y1, int x2, int y2, double *dx, double *dy)
{
	int steps = MAX(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (x1 - x2);
	*dx /= steps;

	*dy = (y1 - y2);
	*dy /= steps;
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

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer = malloc(length);
	memset(buffer, 0, length);
	fread(buffer, 1, length, file);

	fclose(file);

	return buffer;
}
