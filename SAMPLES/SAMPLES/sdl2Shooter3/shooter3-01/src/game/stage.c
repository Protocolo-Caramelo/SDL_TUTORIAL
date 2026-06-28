/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "../system/textures.h"
#include "camera.h"
#include "effects.h"
#include "entities.h"
#include "entityFactory.h"
#include "stage.h"
#include "starfield.h"

static void logic(void);
static void doStage(void);
static void draw(void);

extern App   app;
extern Stage stage;

static SDL_Texture *background;

void initStage(void)
{
	initStarfield();

	initEntities();

	initEffects();

	initEntity("player");

	background = loadTexture("gfx/backgrounds/default.jpg");

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	doStage();
}

static void doStage(void)
{
	stage.engineEffectTimer -= app.deltaTime;

	doEntities();

	doEffects();

	doStarfield(stage.ssx * 0.75, stage.ssy * 0.75);

	doCamera();

	doBackground(stage.ssx * 0.125 * app.deltaTime, stage.ssy * 0.125 * app.deltaTime);

	if (stage.engineEffectTimer <= 0)
	{
		stage.engineEffectTimer = 1;
	}
}

static void draw(void)
{
	drawBackground(background);

	drawStarfield();

	drawEntities();

	drawEffects();
}
