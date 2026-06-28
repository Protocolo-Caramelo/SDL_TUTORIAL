/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

typedef struct AtlasImage AtlasImage;
typedef struct Texture    Texture;

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

typedef struct
{
	int         x;
	int         y;
	int         sx;
	int         sy;
	AtlasImage *texture;
} ISOObject;

typedef struct
{
	int tile;
} MapTile;

typedef struct
{
	MapTile map[MAP_SIZE][MAP_SIZE];
} World;

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
	double        fontScale;
	struct
	{
		int x;
		int y;
		int buttons[MAX_MOUSE_BUTTONS];
		int visible;
	} mouse;
	struct
	{
		int fps;
		int showFPS;
	} dev;
} App;
