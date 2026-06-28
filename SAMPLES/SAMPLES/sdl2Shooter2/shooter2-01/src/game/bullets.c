/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "../system/util.h"
#include "bullets.h"

extern App   app;
extern Stage stage;

void initBullets(void)
{
	memset(&stage.bulletHead, 0, sizeof(Bullet));
	stage.bulletTail = &stage.bulletHead;
}

Bullet *spawnBullet(void)
{
	Bullet *b;

	b = malloc(sizeof(Bullet));
	memset(b, 0, sizeof(Bullet));
	stage.bulletTail->next = b;
	stage.bulletTail = b;

	return b;
}

void doBullets(void)
{
	Bullet *b, *prev;

	prev = &stage.bulletHead;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		b->x += b->dx * app.deltaTime;
		b->y += b->dy * app.deltaTime;

		if (!collision(b->x, b->y, b->texture->rect.w, b->texture->rect.h, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
		{
			prev->next = b->next;

			if (b == stage.bulletTail)
			{
				stage.bulletTail = prev;
			}

			free(b);

			b = prev;
		}

		prev = b;
	}
}

void drawBullets(void)
{
	Bullet *b;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		blitAtlasImage(b->texture, b->x, b->y, 0, SDL_FLIP_NONE);
	}
}
