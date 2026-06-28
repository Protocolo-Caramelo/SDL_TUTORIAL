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
	int x;
	int y;
} Mouse;

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window   *window;
	Delegate      delegate;
	int           keyboard[MAX_KEYBOARD_KEYS];
	Mouse         mouse;
	Texture       textureHead, *textureTail;
} App;
