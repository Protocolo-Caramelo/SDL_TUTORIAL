/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "../system/util.h"
#include "models.h"

static Model *getModel(char *filename);

static Model head, *tail;

extern App app;

void initModels(void)
{
	memset(&head, 0, sizeof(Model));
	tail = &head;
}

void drawModel(Model *m, SDL_FPoint position, double angle)
{
	int        i, n;
	double     rot;
	SDL_Vertex v;
	Triangle  *t;

	rot = TO_RAIDANS(angle);

	for (i = 0; i < m->numTriangles; i++)
	{
		t = m->triangles[i];

		for (n = 0; n < 3; n++)
		{
			memset(&v, 0, sizeof(SDL_Vertex));

			v.position = position;
			v.position.x += t->points[n].x * cos(rot) - t->points[n].y * sin(rot);
			v.position.y += t->points[n].x * sin(rot) + t->points[n].y * cos(rot);

			v.color = t->colors[n];

			drawVertex(&v);
		}
	}
}

Model *loadModel(char *filename)
{
	int       i, numTriangles, n, r, g, b;
	FILE     *fp;
	Model    *model;
	Triangle *t;

	model = getModel(filename);

	if (model == NULL)
	{
		model = malloc(sizeof(Model));
		memset(model, 0, sizeof(Model));
		tail->next = model;
		tail = model;

		fp = openFile(filename);

		fscanf(fp, "%d", &numTriangles);

		STRCPY(model->filename, filename);
		model->numTriangles = numTriangles;
		model->triangles = malloc(sizeof(Triangle *) * numTriangles);

		memset(model->triangles, 0, sizeof(Triangle *) * numTriangles);

		for (i = 0; i < numTriangles; i++)
		{
			model->triangles[i] = malloc(sizeof(Triangle));

			t = model->triangles[i];

			memset(t, 0, sizeof(Triangle));

			for (n = 0; n < 3; n++)
			{
				fscanf(fp, "%f %f %d %d %d ", &t->points[n].x, &t->points[n].y, &r, &g, &b);

				t->colors[n].r = r;
				t->colors[n].g = g;
				t->colors[n].b = b;
				t->colors[n].a = 255;
			}
		}

		fclose(fp);
	}

	return model;
}

static Model *getModel(char *filename)
{
	Model *m;

	for (m = head.next; m != NULL; m = m->next)
	{
		if (strcmp(m->filename, filename) == 0)
		{
			return m;
		}
	}

	return NULL;
}
