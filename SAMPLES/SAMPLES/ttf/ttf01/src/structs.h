/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

typedef struct
{
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window   *window;
	Delegate      delegate;
} App;
