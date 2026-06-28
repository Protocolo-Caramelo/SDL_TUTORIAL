/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
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
#define MAX_DESCRIPTION_LENGTH 64
#define MAX_FILENAME_LENGTH    256
#define MAX_MESSAGE_LENGTH     512

#define NUM_ATLAS_BUCKETS 64

#define MAX_KEYBOARD_KEYS 350

#define MAX_SND_CHANNELS 16

#define WORLD_WIDTH  512
#define WORLD_HEIGHT 512

#define MAP_TILE_SIZE   32
#define TILE_TYPE_RANGE 10

#define MAP_RENDER_WIDTH  (SCREEN_WIDTH / MAP_TILE_SIZE)
#define MAP_RENDER_HEIGHT (SCREEN_HEIGHT / MAP_TILE_SIZE)

enum
{
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
};

enum
{
	MT_WATER,
	MT_SHALLOWS,
	MT_DESERT,
	MT_SAVANNAH,
	MT_LAND,
	MT_FOREST,
	MT_MOUNTAINS,
	MT_SNOW,
	MT_MAX
};
