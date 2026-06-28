/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'
#define STRCPY(dest, src)             \
	strncpy(dest, src, sizeof(dest)); \
	dest[sizeof(dest) - 1] = '\0'

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 900

#define FPS        60.0
#define LOGIC_RATE (FPS / 1000)

#define MAX_NAME_LENGTH        32
#define MAX_DESCRIPTION_LENGTH 256
#define MAX_LINE_LENGTH        1024
#define MAX_FILENAME_LENGTH    1024

#define MAX_KEYBOARD_KEYS 350
#define MAX_MOUSE_BUTTONS 8

#define MAX_SND_CHANNELS 16

#define NUM_ATLAS_BUCKETS 32

#define MAX_TILES 100

#define MAP_TILE_SIZE 48

#define MAP_WIDTH  33
#define MAP_HEIGHT 19

#define MAP_RENDER_WIDTH  32
#define MAP_RENDER_HEIGHT 18

#define MAP_RENDER_X ((SCREEN_WIDTH - (MAP_RENDER_WIDTH * MAP_TILE_SIZE)) / 2)
#define MAP_RENDER_Y ((SCREEN_HEIGHT - (MAP_RENDER_HEIGHT * MAP_TILE_SIZE)) / 2)

#define TILE_HOLE   0
#define TILE_GROUND 1
#define TILE_WALL   50

enum
{
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
};

enum
{
	ET_UKNOWN,
	ET_PLAYER
};

enum
{
	FACING_RIGHT,
	FACING_LEFT
};
