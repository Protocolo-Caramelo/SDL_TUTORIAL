/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

#include <sys/stat.h>

#include "../common.h"

#include "util.h"

uint8_t collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

uint8_t pointInTriangle(double px, double py, double x1, double y1, double x2, double y2, double x3, double y3)
{
	double lambda1, lambda2, lambda3;

	lambda1 = ((y2 - y3) * (px - x3) + (x3 - x2) * (py - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
	lambda2 = ((y3 - y1) * (px - x3) + (x1 - x3) * (py - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
	lambda3 = 1 - lambda1 - lambda2;

	return (lambda1 >= 0 && lambda1 <= 1 && lambda2 >= 0 && lambda2 <= 1 && lambda3 >= 0 && lambda3 <= 1);
}

uint8_t lineLineCollision(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	double denominator, numerator1, numerator2, r, s;

	denominator = ((x2 - x1) * (y4 - y3)) - ((y2 - y1) * (x4 - x3));

	if (denominator == 0)
	{
		return 0;
	}

	numerator1 = ((y1 - y3) * (x4 - x3)) - ((x1 - x3) * (y4 - y3));
	numerator2 = ((y1 - y3) * (x2 - x1)) - ((x1 - x3) * (y2 - y1));

	r = numerator1 / denominator;
	s = numerator2 / denominator;

	return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

uint8_t circleCircleCollision(int x1, int y1, int r1, int x2, int y2, int r2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) <= r1 + r2;
}

uint8_t lineCircleCollision(double x1, double y1, double x2, double y2, double cx, double cy, double r)
{
	double dx, dy, a, b, c, t;

	dx = x2 - x1;
	dy = y2 - y1;
	a = dx * dx + dy * dy;
	b = 2 * ((dx * (x1 - cx)) + (dy * (y1 - cy)));
	c = (cx - x1) * (cx - x1) + (cy - y1) * (cy - y1) - r * r;

	// Check if the line segment intersects the circle.
	if (a == 0)
	{  // Line is a point.
		return c >= 0;
	}
	else
	{
		// Check if the discriminant is negative.
		if (b * b - 4 * a * c < 0)
		{
			return 0;
		}

		// Check if the point of intersection is within the line segment.
		t = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

		if (t < 0 || t > 1)
		{
			return 0;
		}

		return 1;
	}
}

void normalizeVector(int x1, int y1, int x2, int y2, double *dx, double *dy)
{
	long length;

	*dx = x1 - x2;
	*dy = y1 - y2;

	length = sqrt(*dx * *dx + *dy * *dy);

	*dx /= length;
	*dy /= length;
}

uint8_t fileExists(const char *filename)
{
	struct stat buffer;

	return (stat(filename, &buffer) == 0);
}

FILE *openFile(char *filename)
{
	FILE *file;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading '%s' ...", filename);

	file = fopen(filename, "rb");

	if (file == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "No such file '%s'", filename);
		exit(1);
	}

	return file;
}

char *readFile(char *filename)
{
	char *buffer;
	long  length;
	FILE *file;

	file = openFile(filename);

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer = malloc(length);
	memset(buffer, 0, length);
	fread(buffer, 1, length, file);

	fclose(file);

	return buffer;
}

uint8_t writeFile(const char *filename, const char *data)
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

void *resize(void *array, int oldSize, int newSize)
{
	void **newArray;
	int    copySize;

	copySize = newSize > oldSize ? oldSize : newSize;

	newArray = malloc(newSize);
	memset(newArray, 0, newSize);
	memcpy(newArray, array, copySize);
	free(array);

	return newArray;
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
