/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "draw.h"
#include "text.h"

extern App app;

static PointF backgroundPoint[4];

static void showFPS(void);

void initDraw(void)
{
	backgroundPoint[0].x = -SCREEN_WIDTH / 2;
	backgroundPoint[0].y = -SCREEN_HEIGHT / 2;

	backgroundPoint[1].x = SCREEN_WIDTH / 2;
	backgroundPoint[1].y = -SCREEN_HEIGHT / 2;

	backgroundPoint[2].x = -SCREEN_WIDTH / 2;
	backgroundPoint[2].y = SCREEN_HEIGHT / 2;

	backgroundPoint[3].x = SCREEN_WIDTH / 2;
	backgroundPoint[3].y = SCREEN_HEIGHT / 2;
}

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	if (app.dev.showFPS)
	{
		showFPS();
	}

	SDL_RenderPresent(app.renderer);
}

static void showFPS(void)
{
	char fps[8];

	memset(fps, 0, sizeof(fps));

	sprintf(fps, "%dfps", app.dev.fps);

	drawText(fps, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 35, 255, 255, 255, TEXT_ALIGN_CENTER, 0);
}

void blit(SDL_Texture *texture, int x, int y, int center, SDL_RendererFlip flip)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, 0, NULL, flip);
}

void blitAtlasImage(AtlasImage *atlasImage, int x, int y, int center, SDL_RendererFlip flip)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = atlasImage->rect.w;
	dest.h = atlasImage->rect.h;

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopyEx(app.renderer, atlasImage->texture, &atlasImage->rect, &dest, 0, NULL, flip);
}

void blitAtlasImageScaled(AtlasImage *atlasImage, int x, int y, int w, int h, int center)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	if (center)
	{
		dest.x -= w / 2;
		dest.y -= h / 2;
	}

	SDL_RenderCopyEx(app.renderer, atlasImage->texture, &atlasImage->rect, &dest, 0, NULL, SDL_FLIP_NONE);
}

void blitRotated(AtlasImage *atlasImage, int x, int y, double angle)
{
	SDL_Rect dstRect;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = atlasImage->rect.w;
	dstRect.h = atlasImage->rect.h;

	dstRect.x -= (dstRect.w / 2);
	dstRect.y -= (dstRect.h / 2);

	SDL_RenderCopyEx(app.renderer, atlasImage->texture, &atlasImage->rect, &dstRect, angle, NULL, SDL_FLIP_NONE);
}

void drawRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawBlendMode(app.renderer, a < 255 ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
	SDL_RenderFillRect(app.renderer, &rect);
}

void drawOutlineRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawBlendMode(app.renderer, a < 255 ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
	SDL_RenderDrawRect(app.renderer, &rect);
}

void drawCircle(int cx, int cy, int radius, int r, int g, int b, int a)
{
	int       x = radius;
	int       y = 0;
	int       radiusError = 1 - x;
	SDL_Point p[8];

	SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);

	while (x >= y)
	{
		p[0].x = x + cx;
		p[0].y = y + cy;
		p[1].x = y + cx;
		p[1].y = x + cy;
		p[2].x = -x + cx;
		p[2].y = y + cy;
		p[3].x = -y + cx;
		p[3].y = x + cy;
		p[4].x = -x + cx;
		p[4].y = -y + cy;
		p[5].x = -y + cx;
		p[5].y = -x + cy;
		p[6].x = x + cx;
		p[6].y = -y + cy;
		p[7].x = y + cx;
		p[7].y = -x + cy;
		SDL_RenderDrawPoints(app.renderer, p, 8);

		y++;

		if (radiusError < 0)
		{
			radiusError += 2 * y + 1;
		}
		else
		{
			x--;
			radiusError += 2 * (y - x) + 1;
		}
	}

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

void doBackground(double x, double y)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		backgroundPoint[i].x += x;
		backgroundPoint[i].y += y;

		if (backgroundPoint[i].x < 0)
		{
			backgroundPoint[i].x += (SCREEN_WIDTH * 2);
		}

		if (backgroundPoint[i].x >= SCREEN_WIDTH)
		{
			backgroundPoint[i].x -= (SCREEN_WIDTH * 2);
		}

		if (backgroundPoint[i].y < 0)
		{
			backgroundPoint[i].y += (SCREEN_HEIGHT * 2);
		}

		if (backgroundPoint[i].y >= SCREEN_HEIGHT)
		{
			backgroundPoint[i].y -= (SCREEN_HEIGHT * 2);
		}
	}
}

void drawBackground(SDL_Texture *texture)
{
	int      i;
	SDL_Rect dstRect;

	for (i = 0; i < 4; i++)
	{
		dstRect.x = backgroundPoint[i].x;
		dstRect.y = backgroundPoint[i].y;
		dstRect.w = SCREEN_WIDTH;
		dstRect.h = SCREEN_HEIGHT;

		SDL_RenderCopy(app.renderer, texture, NULL, &dstRect);
	}
}
