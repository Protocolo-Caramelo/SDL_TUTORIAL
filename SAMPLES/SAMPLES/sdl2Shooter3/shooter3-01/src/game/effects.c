/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/util.h"
#include "effects.h"

static void engineTick(Effect *e);

static AtlasImage *engineTexture;

extern App   app;
extern Stage stage;

void initEffects(void)
{
	stage.effectTail = &stage.effectHead;

	engineTexture = getAtlasImage("gfx/effects/engine.png", 1);
}

void doEffects(void)
{
	Effect *e, *prev;

	prev = &stage.effectHead;

	for (e = stage.effectHead.next; e != NULL; e = e->next)
	{
		e->tick(e);

		if (e->health <= 0)
		{
			prev->next = e->next;

			free(e);

			if (e == stage.effectTail)
			{
				stage.effectTail = prev;
			}

			e = prev;
		}

		prev = e;
	}
}

void drawEffects(void)
{
	Effect *e;
	int     x, y;

	SDL_SetTextureBlendMode(engineTexture->texture, SDL_BLENDMODE_ADD);

	for (e = stage.effectHead.next; e != NULL; e = e->next)
	{
		x = e->x - stage.camera.x;
		y = e->y - stage.camera.y;

		if (collision(x - (e->texture->rect.w / 2), y - (e->texture->rect.h / 2), e->texture->rect.w, e->texture->rect.w, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
		{
			SDL_SetTextureColorMod(engineTexture->texture, e->color.r, e->color.g, e->color.b);
			SDL_SetTextureAlphaMod(engineTexture->texture, e->color.a);

			blitAtlasImage(e->texture, x, y, 1, SDL_FLIP_NONE);
		}
	}

	SDL_SetTextureColorMod(engineTexture->texture, 255, 255, 255);
	SDL_SetTextureAlphaMod(engineTexture->texture, 255);

	SDL_SetTextureBlendMode(engineTexture->texture, SDL_BLENDMODE_BLEND);
}

static Effect *spawnEffect(int x, int y)
{
	Effect *e;

	e = malloc(sizeof(Effect));
	memset(e, 0, sizeof(Effect));
	stage.effectTail->next = e;
	stage.effectTail = e;

	e->x = x;
	e->y = y;

	e->color.r = e->color.g = e->color.b = e->color.a = 255;

	return e;
}

void addEngineEffect(int x, int y)
{
	Effect *e;

	e = spawnEffect(x, y);
	e->texture = engineTexture;

	e->color.r = 64;
	e->color.g = 128;
	e->color.b = 255;
	e->color.a = 96 + rand() % 64;

	e->health = e->color.a;

	e->tick = engineTick;
}

static void engineTick(Effect *e)
{
	e->health -= 5 * app.deltaTime;

	e->color.a = MAX(e->health, 0);
}
