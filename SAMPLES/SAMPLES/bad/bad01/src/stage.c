/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "draw.h"
#include "stage.h"

extern App app;

static void logic(void);
static void draw(void);

static SDL_Texture *targetterTexture;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	targetterTexture = loadTexture("gfx/targetter.png");
}

static void logic(void)
{
}

static void draw(void)
{
	blit(targetterTexture, app.mouse.x, app.mouse.y, 1);
}
