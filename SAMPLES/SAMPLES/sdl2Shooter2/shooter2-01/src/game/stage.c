/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/bullets.h"
#include "../game/entities.h"
#include "../game/hud.h"
#include "../game/player.h"
#include "../game/stars.h"
#include "../system/draw.h"
#include "../system/textures.h"
#include "stage.h"

extern App   app;
extern Stage stage;

static void logic(void);
static void draw(void);
static void drawBackground(void);

static SDL_Texture *background;
static double       backgroundY;

void initStage(void)
{
	memset(&stage, 0, sizeof(Stage));

	initEntities();

	initPlayer();

	initStars();

	initBullets();

	background = loadTexture("gfx/background.jpg");

	backgroundY = -SCREEN_HEIGHT;

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	backgroundY += app.deltaTime;

	if (backgroundY >= 0)
	{
		backgroundY = -SCREEN_HEIGHT;
	}

	doStars();

	doPlayer();

	doBullets();
}

static void draw(void)
{
	drawBackground();

	drawStars();

	drawEntities();

	drawBullets();

	drawHud();
}

static void drawBackground(void)
{
	double y;

	for (y = backgroundY; y < SCREEN_HEIGHT; y += SCREEN_HEIGHT)
	{
		blit(background, 0, y, 0, SDL_FLIP_NONE);
	}
}
