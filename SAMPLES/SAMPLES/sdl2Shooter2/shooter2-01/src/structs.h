/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

typedef struct Texture    Texture;
typedef struct Bullet     Bullet;
typedef struct AtlasImage AtlasImage;
typedef struct Star       Star;
typedef struct Entity     Entity;

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
	AtlasImage *texture;
	void(*data);
	Entity *next;
};

typedef struct
{
	double reload;
	int    reloadRate;
	double speed;
} Fighter;

struct Bullet
{
	double      x;
	double      y;
	double      dx;
	double      dy;
	AtlasImage *texture;
	Entity     *owner;
	Bullet     *next;
};

struct Star
{
	double x;
	double y;
	double speed;
};

typedef struct
{
	Entity entityHead, *entityTail;
	Bullet bulletHead, *bulletTail;
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
	double        deltaTime;
	struct
	{
		int fps;
		int showFPS;
	} dev;
} App;
