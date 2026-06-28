/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "demo.h"
#include "draw.h"
#include "text.h"

extern App app;

static void logic(void);
static void draw(void);
static void drawNormalText(void);
static void drawScaledText(void);
static void drawRotatedText(void);
static void drawColouredText(void);

static SDL_Texture *helloWorld;
static int          textAngle;

void initDemo(void)
{
	helloWorld = getTextTexture("Hello World!");

	textAngle = 0;

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	textAngle++;
}

static void draw(void)
{
	drawNormalText();

	drawScaledText();

	drawRotatedText();

	drawColouredText();
}

static void drawNormalText(void)
{
	blit(helloWorld, 50, 50, 0);
}

static void drawScaledText(void)
{
	blitScaled(helloWorld, 50, 125, 500, 40);
}

static void drawRotatedText(void)
{
	blitRotated(helloWorld, 60, 300, 90);

	blitRotated(helloWorld, 150, 300, -90);

	blitRotated(helloWorld, 600, 300, textAngle);
}

static void drawColouredText(void)
{
	SDL_SetTextureColorMod(helloWorld, 255, 0, 0);

	blit(helloWorld, 275, 200, 0);

	SDL_SetTextureColorMod(helloWorld, 0, 255, 0);

	blit(helloWorld, 275, 250, 0);

	SDL_SetTextureColorMod(helloWorld, 0, 0, 255);

	blit(helloWorld, 275, 300, 0);

	SDL_SetTextureColorMod(helloWorld, 255, 255, 255);
	SDL_SetTextureAlphaMod(helloWorld, 64);

	blit(helloWorld, 275, 350, 0);

	SDL_SetTextureAlphaMod(helloWorld, 255);
}
