/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRCPY(dest, src)             \
	strncpy(dest, src, sizeof(dest)); \
	dest[sizeof(dest) - 1] = '\0'
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 900

#define FPS                      60
#define LOGIC_RATE               (FPS * 1.0 / 1000)
#define PI                       3.14159265358979323846
#define TO_RAIDANS(angleDegrees) (angleDegrees * PI / 180.0)

#define MAX_NAME_LENGTH        32
#define MAX_LINE_LENGTH        1024
#define MAX_INPUT_LENGTH       16
#define MAX_FILENAME_LENGTH    256
#define MAX_DESCRIPTION_LENGTH 256

#define MAX_KEYBOARD_KEYS  350
#define MAX_MOUSE_BUTTONS  8
#define MAX_JOYPAD_BUTTONS 16
#define DEADZONE_MAX       32000

#define MAX_SND_CHANNELS 16

#define MAX_STARS 350

enum
{
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
};

enum
{
	WT_BUTTON,
	WT_SLIDER,
	WT_CONTROL,
	WT_TOGGLE
};

enum
{
	JOYPAD_AXIS_X,
	JOYPAD_AXIS_Y,
	JOYPAD_AXIS_MAX
};

enum
{
	CONTROL_LEFT,
	CONTROL_RIGHT,
	CONTROL_UP,
	CONTROL_DOWN,
	CONTROL_FIRE,
	CONTROL_SECONDARY,
	CONTROL_PAUSE,
	CONTROL_MAX
};

enum
{
	FACING_LEFT,
	FACING_RIGHT
};

enum
{
	SND_MAX
};
