/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

#define MAX_TILES 8

#define TILE_SIZE 64

#define MAP_WIDTH  40
#define MAP_HEIGHT 20

#define MAP_RENDER_WIDTH  20
#define MAP_RENDER_HEIGHT 12

#define MAX_NAME_LENGTH     32
#define MAX_FILENAME_LENGTH 1024

#define MAX_KEYBOARD_KEYS 350

#define MAX_SND_CHANNELS 16
