/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "util.h"

static ExpiringString stringHead, *stringTail;

void initUtils(void)
{
	memset(&stringHead, 0, sizeof(ExpiringString));
	stringTail = &stringHead;
}

void expireStrings(void)
{
	ExpiringString *s;

	while (stringHead.next != NULL)
	{
		s = stringHead.next;

		stringHead.next = s->next;

		free(s->string);
		free(s);
	}

	stringTail = &stringHead;
}

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

	return abs(hash);
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

void hsvToRGB(double h, double s, double v, double *r, double *g, double *b)
{
	double c, x, m;

	c = v * s;
	h = fmod(h / 60.0, 6);
	x = c * (1 - fabs(fmod(h, 2) - 1));
	m = v - c;

	*r = 0;
	*g = 0;
	*b = 0;

	if (h >= 0 && h < 1)
	{
		*r = c;
		*g = x;
	}
	else if (h >= 1 && h < 2)
	{
		*r = x;
		*g = c;
	}
	else if (h >= 2 && h < 3)
	{
		*g = c;
		*b = x;
	}
	else if (h >= 3 && h < 4)
	{
		*g = x;
		*b = c;
	}
	else if (h >= 4 && h < 5)
	{
		*r = x;
		*b = c;
	}
	else if (h < 6)
	{
		*r = c;
		*b = x;
	}

	*r += m;
	*g += m;
	*b += m;

	*r *= 255;
	*g *= 255;
	*b *= 255;
}

char *formattedString(const char *format, ...)
{
	int     n;
	char   *rtn;
	va_list args;

	if (format != NULL)
	{
		va_start(args, format);
		n = vsnprintf(NULL, 0, format, args) + 1;
		va_end(args);

		rtn = malloc(n);
		memset(rtn, 0, n);

		va_start(args, format);
		vsprintf(rtn, format, args);
		va_end(args);

		return rtn;
	}

	return NULL;
}

char *expiringFormattedString(const char *format, ...)
{
	int             n;
	va_list         args;
	ExpiringString *s;

	if (format != NULL)
	{
		s = malloc(sizeof(ExpiringString));
		memset(s, 0, sizeof(ExpiringString));
		stringTail->next = s;
		stringTail = s;

		va_start(args, format);
		n = vsnprintf(NULL, 0, format, args) + 1;
		va_end(args);

		s->string = malloc(n);
		memset(s->string, 0, n);

		va_start(args, format);
		vsprintf(s->string, format, args);
		va_end(args);

		return s->string;
	}

	return NULL;
}
