/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

typedef struct Entity   Entity;
typedef struct Triangle Triangle;
typedef struct Model    Model;

struct Triangle
{
	SDL_FPoint points[3];
	SDL_Color  colors[3];
	Triangle  *next;
};

struct Model
{
	char       filename[MAX_FILENAME_LENGTH];
	int        numTriangles;
	Triangle **triangles;
	Model     *next;
};

struct Entity
{
	uint8_t    type;
	SDL_FPoint position;
	Model     *model;
	double     angle;
	void (*tick)(Entity *self);
	void (*draw)(Entity *self);
	Entity *next;
};

typedef struct
{
	Entity entityHead, *entityTail;
} Zone;

typedef struct
{
	struct
	{
		void (*logic)(void);
		void (*draw)(void);
	} delegate;
	double        deltaTime;
	uint8_t       keyboard[MAX_KEYBOARD_KEYS];
	double        transitionTimer;
	SDL_Renderer *renderer;
	SDL_Window   *window;
} App;
