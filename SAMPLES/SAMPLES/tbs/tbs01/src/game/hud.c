/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "hud.h"

extern App   app;
extern Stage stage;

static void drawSelectedTile(void);
static void doSelectedTile(void);

static AtlasImage *selectedTileTexture;
static double      selectedTilePulse;

void initHud(void)
{
	selectedTileTexture = getAtlasImage("gfx/hud/selectedTile.png", 1);

	selectedTilePulse = 0;
}

void doHud(void)
{
	doSelectedTile();
}

static void doSelectedTile(void)
{
	selectedTilePulse += 0.1 * app.deltaTime;

	stage.selectedTile.x = (app.mouse.x / MAP_TILE_SIZE);
	stage.selectedTile.y = (app.mouse.y / MAP_TILE_SIZE);

	stage.selectedTile.x = MIN(MAX(stage.selectedTile.x, 0), MAP_WIDTH - 1);
	stage.selectedTile.y = MIN(MAX(stage.selectedTile.y, 0), MAP_HEIGHT - 1);
}

void drawHud(void)
{
	if (!stage.animating)
	{
		drawSelectedTile();
	}
}

static void drawSelectedTile(void)
{
	double pulse;
	int    x, y;

	pulse = (sin(selectedTilePulse) + 1) / 2;

	SDL_SetTextureAlphaMod(selectedTileTexture->texture, 127 + (128 * pulse));

	x = (stage.selectedTile.x * MAP_TILE_SIZE);
	y = (stage.selectedTile.y * MAP_TILE_SIZE);

	blitAtlasImage(selectedTileTexture, x, y, 0, SDL_FLIP_NONE);

	SDL_SetTextureAlphaMod(selectedTileTexture->texture, 255);
}
