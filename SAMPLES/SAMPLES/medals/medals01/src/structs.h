/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

typedef struct AtlasImage AtlasImage;
typedef struct Texture    Texture;
typedef struct Medal      Medal;
typedef struct Lookup     Lookup;

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

struct Lookup
{
	char    name[MAX_NAME_LENGTH];
	long    value;
	Lookup *next;
};

struct Medal
{
	char          id[MAX_NAME_LENGTH];
	char          title[MAX_NAME_LENGTH];
	char          description[MAX_DESCRIPTION_LENGTH];
	int           type;
	int           notify;
	int           hidden;
	unsigned long awardDate;
	Medal        *next;
};

typedef struct
{
	Medal medalsHead;
} Game;

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
		int fps;
	} dev;
} App;
