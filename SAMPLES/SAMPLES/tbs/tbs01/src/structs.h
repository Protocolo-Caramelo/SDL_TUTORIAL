/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

typedef struct AtlasImage AtlasImage;
typedef struct Texture    Texture;
typedef struct Entity     Entity;
typedef struct InitFunc   InitFunc;
typedef struct Node       Node;

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

struct InitFunc
{
	char name[MAX_NAME_LENGTH];
	void (*init)(Entity *e);
	InitFunc *next;
};

struct Node
{
	int   x;
	int   y;
	int   g;
	int   f;
	int   h;
	int   closed;
	Node *parent;
	Node *next;
};

struct Entity
{
	unsigned int id;
	int          type;
	char         name[MAX_NAME_LENGTH];
	int          x;
	int          y;
	int          side;
	int          solid;
	int          facing;
	AtlasImage  *texture;
	void (*draw)(Entity *self);
	Entity *next;
};

typedef struct
{
	int tile;
} MapTile;

typedef struct
{
	unsigned int entityId;
	MapTile      map[MAP_WIDTH][MAP_HEIGHT];
	Entity       entityHead, *entityTail;
	Entity      *currentEntity;
	Node         routeHead;
	int          animating;
	struct
	{
		int x;
		int y;
	} selectedTile;
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
	Uint8        *keys;
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
	} dev;
} App;
