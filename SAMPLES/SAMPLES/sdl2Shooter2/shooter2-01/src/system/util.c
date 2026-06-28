/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
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

char *readFile(char *filename)
{
	char *buffer;
	long  length;
	FILE *file;

	file = fopen(filename, "rb");

	if (file)
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
