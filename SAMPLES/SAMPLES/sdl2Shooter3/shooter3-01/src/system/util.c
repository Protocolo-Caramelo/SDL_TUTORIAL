/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include <sys/stat.h>

#include "../common.h"

unsigned long hashcode(const char *str)
{
	unsigned long hash = 5381;
	int           c;

	c = *str;

	while (c)
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

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

	return angle >= 0 ? angle : 360 + angle;
}

int fileExists(const char *filename)
{
	struct stat buffer;

	return (stat(filename, &buffer) == 0);
}

int getFileModTime(const char *filename)
{
	struct stat buffer;

	if (stat(filename, &buffer) == 0)
	{
		return buffer.st_mtime;
	}

	return -1;
}

char *readFile(char *filename)
{
	char *buffer;
	long  length;
	FILE *file;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s ...", filename);

	file = fopen(filename, "rb");

	buffer = NULL;

	if (file != NULL)
	{
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);

		buffer = malloc(length);
		memset(buffer, 0, length);
		fread(buffer, 1, length, file);

		fclose(file);
	}

	return buffer;
}

int writeFile(const char *filename, const char *data)
{
	FILE *file;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Saving %s ...", filename);

	file = fopen(filename, "wb");

	if (file)
	{
		fprintf(file, "%s\n", data);
		fclose(file);
		return 1;
	}

	return 0;
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

char **toArray(char *in, int *count)
{
	int   i;
	char *val, **rtn;

	*count = 0;

	rtn = NULL;

	if (strlen(in) > 0)
	{
		*count = 1;

		for (i = 0; i < strlen(in); i++)
		{
			if (in[i] == ',')
			{
				*count = *count + 1;
			}
		}

		rtn = malloc(*count * sizeof(char *));

		i = 0;

		val = strtok(in, ",");

		while (val)
		{
			rtn[i] = malloc(strlen(val) + 1);

			strcpy(rtn[i], val);

			val = strtok(NULL, ",");

			i++;
		}
	}

	return rtn;
}
