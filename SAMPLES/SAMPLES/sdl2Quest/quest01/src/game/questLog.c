/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "../system/text.h"
#include "../system/util.h"
#include "questLog.h"

#define MAP_SCALE 1.5

extern App  app;
extern Game game;

static void logic(void);
static void doControls(void);
static void draw(void);
static void drawMap(void);
static void genMiniMap(void);
static void drawSectionBar(void);
static void setMapTileColor(int type, int *r, int *g, int *b);
static void (*closeQuestLog)(void);

static int show;

void initQuestLog(void)
{
	genMiniMap();
}

void openQuestLog(void (*rtn)(void))
{
	show = 0;

	closeQuestLog = rtn;

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	doControls();
}

static void doControls(void)
{
	if (app.keyboard[SDL_SCANCODE_TAB])
	{
		closeQuestLog();

		app.transitionTimer = FPS / 4;

		app.keyboard[SDL_SCANCODE_TAB] = 0;
	}
}

static void draw(void)
{
	drawSectionBar();

	drawMap();
}

static void drawSectionBar(void)
{
	int x;

	x = 700 / 4;

	drawRect((x * show) + 5, 5, x - 10, 36, 64, 255, 255, 32);
	drawOutlineRect((x * show) + 5, 5, x - 10, 36, 64, 255, 255, 255);

	drawText("Quests", x / 2, 5, 255, 255, 255, TEXT_ALIGN_CENTER, 0);

	drawText("Islands", x + (x / 2), 5, 255, 255, 255, TEXT_ALIGN_CENTER, 0);

	drawText("Towns", (x * 2) + (x / 2), 5, 255, 255, 255, TEXT_ALIGN_CENTER, 0);

	drawText("Inventory", (x * 3) + (x / 2), 5, 255, 255, 255, TEXT_ALIGN_CENTER, 0);
}

static void drawMap(void)
{
	SDL_Rect dest;

	dest.w = WORLD_WIDTH * MAP_SCALE;
	dest.h = WORLD_HEIGHT * MAP_SCALE;
	dest.y = (SCREEN_HEIGHT - dest.h) / 2;
	dest.x = (SCREEN_WIDTH - dest.w) - dest.y;

	SDL_RenderCopy(app.renderer, game.overworld.miniMapTexture, NULL, &dest);

	drawText(expiringFormattedString("World #%X", game.overworld.seed), dest.x + (dest.w / 2), dest.y + dest.h + 5, 255, 255, 255, TEXT_ALIGN_CENTER, 0);
}

static void genMiniMap(void)
{
	int x, y, r, g, b;

	game.overworld.miniMapTexture = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WORLD_WIDTH, WORLD_HEIGHT);

	SDL_SetRenderTarget(app.renderer, game.overworld.miniMapTexture);

	for (x = 0; x < WORLD_WIDTH; x++)
	{
		for (y = 0; y < WORLD_HEIGHT; y++)
		{
			setMapTileColor(game.map->data[x][y], &r, &g, &b);

			SDL_SetRenderDrawColor(app.renderer, r, g, b, 255);
			SDL_RenderDrawPoint(app.renderer, x, y);
		}
	}

	SDL_SetRenderTarget(app.renderer, NULL);
}

static void setMapTileColor(int type, int *r, int *g, int *b)
{
	double adj;

	adj = 1.0;

	switch (type)
	{
		case MT_WATER:
			adj = 0.2;
			break;

		case MT_SHALLOWS:
			adj = 0.35;
			break;

		case MT_DESERT:
		case MT_SAVANNAH:
		case MT_LAND:
			adj = 0.5;
			break;

		case MT_FOREST:
			adj = 0.6;
			break;

		case MT_MOUNTAINS:
			adj = 0.8;
			break;

		default:
			adj = 1.0;
			break;
	}

	*r = 200 * adj;
	*g = 200 * adj;
	*b = 255 * adj;
}
