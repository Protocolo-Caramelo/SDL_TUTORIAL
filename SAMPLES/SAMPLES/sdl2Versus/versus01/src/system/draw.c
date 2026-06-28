/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "draw.h"

#define VERTEX_CAPACITY (1024 * 3)

static int        vIndex;
static SDL_Vertex vertices[VERTEX_CAPACITY];

extern App app;

void initDraw(void)
{
	vIndex = 0;
}

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);

	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	flushGeometry();

	SDL_RenderPresent(app.renderer);
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

void drawLine(double x1, double y1, double x2, double y2, int r, int g, int b, int a)
{
	SDL_SetRenderDrawBlendMode(app.renderer, a < 255 ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
	SDL_RenderDrawLine(app.renderer, x1, y1, x2, y2);
}

void drawVertex(SDL_Vertex *v)
{
	if (vIndex == VERTEX_CAPACITY)
	{
		flushGeometry();
	}

	vertices[vIndex++] = *v;
}

void flushGeometry(void)
{
	SDL_RenderGeometry(app.renderer, NULL, vertices, vIndex, NULL, 0);

	vIndex = 0;
}
