/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

typedef struct Entity     Entity;
typedef struct AtlasImage AtlasImage;
typedef struct Texture    Texture;
typedef struct InitFunc   InitFunc;

struct AtlasImage
{
	char         filename[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	SDL_Rect     rect;
	int          rotated;
	AtlasImage  *next;
};

struct Texture
{
	char         name[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	Texture     *next;
};

struct Entity
{
	int         id;
	int         type;
	char        name[MAX_NAME_LENGTH];
	int         x;
	int         y;
	int         facing;
	AtlasImage *texture;
	Entity     *next;
};

struct InitFunc
{
	char name[MAX_NAME_LENGTH];
	void (*init)(Entity *e);
	InitFunc *next;
};

typedef struct
{
	int tile;
	int visible;
	int revealed;
} MapTile;

typedef struct
{
	int       entityId;
	Entity    entityHead, *entityTail;
	Entity   *player;
	MapTile   map[MAP_WIDTH][MAP_HEIGHT];
	SDL_Point camera;
} Dungeon;

typedef struct
{
	struct
	{
		void (*logic)(void);
		void (*draw)(void);
	} delegate;

	double        deltaTime;
	double        fontScale;
	SDL_Renderer *renderer;
	SDL_Window   *window;
	int           keyboard[MAX_KEYBOARD_KEYS];

	struct
	{
		int fps;
	} dev;
} App;
