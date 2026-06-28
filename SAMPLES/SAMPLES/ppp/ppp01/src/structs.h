/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

typedef struct Texture Texture;

typedef struct
{
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

struct Texture
{
	char         name[MAX_NAME_LENGTH];
	SDL_Texture *texture;
	Texture     *next;
};

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window   *window;
	Delegate      delegate;
	int           keyboard[MAX_KEYBOARD_KEYS];
	Texture       textureHead, *textureTail;
} App;

typedef struct
{
	int map[MAP_WIDTH][MAP_HEIGHT];
} Stage;
