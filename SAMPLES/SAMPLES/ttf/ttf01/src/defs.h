/*
 * Copyright (C) 2021-2022 Parallel Realities.
 */

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

#define MAX_FILENAME_LENGTH 256

#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'
