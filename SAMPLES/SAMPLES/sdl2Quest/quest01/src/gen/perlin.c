/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#define PERMUTATION_SIZE 256

static void   initPermutation(int seed);
static double perlin(double x, double y);

static int p[PERMUTATION_SIZE * 2];

double **generatePerlinNoise(int width, int height, int seed)
{
	double **noise, nx, ny, v, s;
	int      i, x, y;

	noise = (double **)malloc(width * sizeof(double *));

	for (i = 0; i < width; i++)
	{
		noise[i] = (double *)malloc(height * sizeof(double));
	}

	initPermutation(seed);

	for (x = 0; x < width; x++)
	{
		for (y = 0; y < height; y++)
		{
			s = 3;

			nx = ((s * x) / width) - 0.5;
			ny = ((s * y) / height) - 0.5;

			v = 0;

			v += perlin(nx, ny);
			v += perlin(nx * 2, ny * 2) * 0.5;
			v += perlin(nx * 4, ny * 4) * 0.25;
			v += perlin(nx * 8, ny * 8) * 0.125;

			v /= (1 + 0.5 + 0.25 + 0.125);

			v = pow(v, 1.35);

			noise[x][y] = v;
		}
	}

	return noise;
}

static void initPermutation(int seed)
{
	int i, j, temp;

	for (i = 0; i < PERMUTATION_SIZE; i++)
	{
		p[i] = i;
	}

	srand(seed);

	for (i = PERMUTATION_SIZE - 1; i > 0; i--)
	{
		j = rand() % (i + 1);
		temp = p[i];
		p[i] = p[j];
		p[j] = temp;
	}

	for (i = 0; i < PERMUTATION_SIZE; i++)
	{
		p[PERMUTATION_SIZE + i] = p[i];
	}
}

static double fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

static double lerp(double a, double b, double t)
{
	return a + t * (b - a);
}

static double grad(int hash, double x, double y)
{
	int    h = hash & 3;
	double u = h < 2 ? x : y;
	double v = h < 2 ? y : x;

	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

static double perlin(double x, double y)
{
	int    xi, yi, aa, ab, ba, bb;
	double xf, yf, u, v, x1, x2;

	xi = (int)floor(x) & 255;
	yi = (int)floor(y) & 255;

	xf = x - floor(x);
	yf = y - floor(y);

	u = fade(xf);
	v = fade(yf);

	aa = p[p[xi] + yi];
	ab = p[p[xi] + yi + 1];
	ba = p[p[xi + 1] + yi];
	bb = p[p[xi + 1] + yi + 1];

	x1 = lerp(grad(aa, xf, yf), grad(ab, xf, yf - 1), v);
	x2 = lerp(grad(ba, xf - 1, yf), grad(bb, xf - 1, yf - 1), v);

	return (lerp(x1, x2, u) + 1) / 2;
}

void freePerlin(double **noise, int height)
{
	int i;

	for (i = 0; i < height; i++)
	{
		free(noise[i]);
	}

	free(noise);
}
