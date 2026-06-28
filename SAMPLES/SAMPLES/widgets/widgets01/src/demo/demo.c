/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/widgets.h"
#include "demo.h"

extern App app;

static void logic(void);
static void draw(void);

void initDemo(void)
{
	Widget *w;
	int     x;

	x = 500;

	w = createWidget("start");
	w->x = x;
	w->y = 200;
	STRCPY(w->label, "Start");

	app.activeWidget = w;

	w = createWidget("load");
	w->x = x;
	w->y = 250;
	STRCPY(w->label, "Load");

	w = createWidget("options");
	w->x = x;
	w->y = 300;
	STRCPY(w->label, "Options");

	w = createWidget("credits");
	w->x = x;
	w->y = 350;
	STRCPY(w->label, "Credits");

	w = createWidget("exit");
	w->x = x;
	w->y = 400;
	STRCPY(w->label, "Exit");

	app.delegate.logic = &logic;
	app.delegate.draw = &draw;
}

static void logic(void)
{
	doWidgets();
}

static void draw(void)
{
	drawWidgets();
}
