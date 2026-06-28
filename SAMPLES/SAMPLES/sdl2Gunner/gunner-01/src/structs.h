/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

typedef struct Texture    Texture;
typedef struct AtlasImage AtlasImage;
typedef struct Entity     Entity;
typedef struct InitFunc   InitFunc;

struct Texture
{
	char         name[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	Texture     *next;
};

struct AtlasImage
{
	char         filename[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	SDL_Rect     rect;
	int          rotated;
	AtlasImage  *next;
};

struct Entity
{
	double      x;
	double      y;
	double      dx;
	double      dy;
	int         facing;
	AtlasImage *texture;
	void (*tick)(Entity *self);
	void (*draw)(Entity *self);
	Entity *next;
};

struct InitFunc
{
	char name[MAX_NAME_LENGTH];
	void (*init)(Entity *e);
	InitFunc *next;
};

typedef struct
{
	Entity entityHead, *entityTail;
} Stage;

typedef struct
{
	struct
	{
		void (*logic)(void);
		void (*draw)(void);
	} delegate;
	SDL_Renderer *renderer;
	SDL_Window   *window;
	int           keyboard[MAX_KEYBOARD_KEYS];
	char          inputText[MAX_INPUT_LENGTH];
	int           lastKeyPressed;
	double        deltaTime;
	double        fontScale;
	struct
	{
		int fps;
		int showFPS;
	} dev;
} App;
