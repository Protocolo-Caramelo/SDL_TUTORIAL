/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

typedef struct AtlasImage     AtlasImage;
typedef struct Texture        Texture;
typedef struct ExpiringString ExpiringString;

struct ExpiringString
{
	char		   *string;
	ExpiringString *next;
};

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
	int       width;
	int       height;
	int     **data;
	SDL_Point camera;
} Map;

typedef struct
{
	long         seed;
	Map          map;
	SDL_Texture *miniMapTexture;
} Overworld;

typedef struct
{
	Overworld overworld;
	Map      *map;
	double    time;
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
	double        transitionTimer;
	double        fontScale;
	int           expireStrings;
	struct
	{
		int fps;
	} dev;
} App;
