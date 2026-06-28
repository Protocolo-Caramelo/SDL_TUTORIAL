/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "draw.h"

extern App app;

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 16, 16, 32, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}
