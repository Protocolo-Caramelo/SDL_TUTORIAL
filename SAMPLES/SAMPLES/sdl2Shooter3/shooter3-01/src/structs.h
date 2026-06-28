/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

typedef struct Texture    Texture;
typedef struct Widget     Widget;
typedef struct AtlasImage AtlasImage;
typedef struct Entity     Entity;
typedef struct Effect     Effect;
typedef struct InitFunc   InitFunc;
typedef struct cJSON      cJSON;
typedef struct Lookup     Lookup;

typedef struct
{
	double x;
	double y;
} PointF;

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

struct InitFunc
{
	char name[MAX_NAME_LENGTH];
	void (*init)(Entity *e);
	InitFunc *next;
};

struct Entity
{
	double      x;
	double      y;
	int         facing;
	AtlasImage *texture;
	int         dead;
	void(*data);
	void (*tick)(Entity *self);
	void (*draw)(Entity *self);
	Entity *next;
};

typedef struct
{
	double health;
	int    maxHealth;
	double dx, dy;
} Fighter;

typedef struct
{
	double x;
	double y;
	double speed;
} Star;

struct Effect
{
	double      x;
	double      y;
	double      dx;
	double      dy;
	double      health;
	AtlasImage *texture;
	SDL_Color   color;
	void (*tick)(Effect *self);
	Effect *next;
};

typedef struct
{
	double  ssx, ssy;
	Effect  effectHead, *effectTail;
	Entity  entityHead, *entityTail;
	double  engineEffectTimer;
	Entity *player;
	PointF  camera;
} Stage;

struct Widget
{
	int     type;
	char    name[MAX_NAME_LENGTH];
	char    groupName[MAX_NAME_LENGTH];
	int     x;
	int     y;
	int     w;
	int     h;
	char    label[MAX_NAME_LENGTH];
	int     disabled;
	int     hidden;
	Widget *prev;
	Widget *next;
	void (*action)(void);
	void(*data);
};

typedef struct
{
	SDL_Color color;
} ButtonWidget;

typedef struct
{
	double value;
} SliderWidget;

typedef struct
{
	int   x;
	int   y;
	int   maxLength;
	char *text;
} InputWidget;

typedef struct
{
	int keyboard;
	int joypad;
} ControlWidget;

typedef struct
{
	int on;
} ToggleWidget;

struct Lookup
{
	char    name[MAX_NAME_LENGTH];
	long    value;
	Lookup *next;
};

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
	int           joypadButton[MAX_JOYPAD_BUTTONS];
	int           joypadAxis[JOYPAD_AXIS_MAX];
	SDL_Joystick *joypad;
	int           lastKeyPressed;
	int           lastButtonPressed;
	double        deltaTime;
	Widget       *activeWidget;
	double        fontScale;
	struct
	{
		int keyControls[CONTROL_MAX];
		int joypadControls[CONTROL_MAX];
		int soundVolume;
		int musicVolume;
		int deadzone;
	} config;
	struct
	{
		int x;
		int y;
		int buttons[MAX_MOUSE_BUTTONS];
	} mouse;
	struct
	{
		int fps;
		int showFPS;
	} dev;
} App;
