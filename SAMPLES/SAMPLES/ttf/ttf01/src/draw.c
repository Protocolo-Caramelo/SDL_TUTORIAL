/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "draw.h"

extern App app;

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

void blit(SDL_Texture *texture, int x, int y, int center)
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

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitScaled(SDL_Texture *texture, int x, int y, int w, int h)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRotated(SDL_Texture *texture, int x, int y, int angle)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	dest.x -= dest.w / 2;
	dest.y -= dest.h / 2;

	SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}
