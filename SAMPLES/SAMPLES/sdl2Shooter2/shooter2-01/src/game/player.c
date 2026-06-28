/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/bullets.h"
#include "../game/entities.h"
#include "../system/atlas.h"
#include "player.h"

extern App     app;
extern Entity *player;

static void fireBullet(void);

static AtlasImage *bulletTexture;

void initPlayer(void)
{
	Fighter *f;

	f = malloc(sizeof(Fighter));
	memset(f, 0, sizeof(Fighter));

	f->speed = 4.0;
	f->reloadRate = 20;

	player = spawnEntity();
	player->texture = getAtlasImage("gfx/player.png", 1);
	player->x = (SCREEN_WIDTH - player->texture->rect.w) / 2;
	player->y = SCREEN_HEIGHT - 100;
	player->data = f;

	bulletTexture = getAtlasImage("gfx/playerBullet.png", 1);
}

void doPlayer(void)
{
	Fighter *f;

	f = (Fighter *)player->data;

	f->reload = MAX(f->reload - app.deltaTime, 0);

	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		player->x -= f->speed * app.deltaTime;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->x += f->speed * app.deltaTime;
	}

	if (app.keyboard[SDL_SCANCODE_UP])
	{
		player->y -= f->speed * app.deltaTime;
	}

	if (app.keyboard[SDL_SCANCODE_DOWN])
	{
		player->y += f->speed * app.deltaTime;
	}

	if (app.keyboard[SDL_SCANCODE_LCTRL] && f->reload == 0)
	{
		fireBullet();

		f->reload = f->reloadRate;
	}

	player->x = MIN(MAX(player->x, 0), SCREEN_WIDTH - player->texture->rect.w);
	player->y = MIN(MAX(player->y, 0), SCREEN_HEIGHT - player->texture->rect.h);
}

static void fireBullet(void)
{
	Bullet *b;

	b = spawnBullet();
	b->owner = player;
	b->texture = bulletTexture;
	b->x = player->x + (player->texture->rect.w / 2) - (bulletTexture->rect.w / 2);
	b->y = player->y - bulletTexture->rect.h;
	b->dy = -15;
}
