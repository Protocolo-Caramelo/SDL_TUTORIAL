/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/widgets.h"
#include "controls.h"

static void setupControlWidget(int control, int y);
static void updateControls(void);
static void deadzone(void);

extern App app;

static char   *widgetNames[] = {"left", "right", "up", "down", "fire", "secondary", "pause"};
static Widget *deadzoneWidget;

void initControls(void)
{
	int     i, y;
	Widget *w;

	y = 100;

	for (i = 0; i < CONTROL_MAX; i++)
	{
		setupControlWidget(i, y);

		y += 60;
	}

	deadzoneWidget = getWidget("deadzone", "controls");
	deadzoneWidget->x = (SCREEN_WIDTH - deadzoneWidget->w) / 2;
	deadzoneWidget->y = y + 20;
	deadzoneWidget->action = deadzone;
	((SliderWidget *)deadzoneWidget->data)->value = (1.0 * app.config.deadzone) / DEADZONE_MAX;

	w = getWidget("back", "controls");
	w->x = (SCREEN_WIDTH - w->w) / 2;
	w->y = SCREEN_HEIGHT - 250;

	updateControls();
}

void doControls(void)
{
	doWidgets("controls");
}

void drawControls(void)
{
	drawWidgets("controls");
}

int isControl(int type)
{
	int key, btn;

	if (type == CONTROL_LEFT && app.joypadAxis[JOYPAD_AXIS_X] < -app.config.deadzone)
	{
		return 1;
	}

	if (type == CONTROL_RIGHT && app.joypadAxis[JOYPAD_AXIS_X] > app.config.deadzone)
	{
		return 1;
	}

	if (type == CONTROL_UP && app.joypadAxis[JOYPAD_AXIS_Y] < -app.config.deadzone)
	{
		return 1;
	}

	if (type == CONTROL_DOWN && app.joypadAxis[JOYPAD_AXIS_Y] > app.config.deadzone)
	{
		return 1;
	}

	key = app.config.keyControls[type];

	btn = app.config.joypadControls[type];

	return ((key != 0 && app.keyboard[key]) || (btn != -1 && app.joypadButton[btn]));
}

void clearControl(int type)
{
	int c;

	c = app.config.keyControls[type];

	app.keyboard[c] = 0;

	c = app.config.joypadControls[type];

	if (c != -1)
	{
		app.joypadButton[c] = 0;
	}
}

static void setupControlWidget(int control, int y)
{
	Widget        *w;
	ControlWidget *cw;

	w = getWidget(widgetNames[control], "controls");
	w->w = 700;
	w->x = (SCREEN_WIDTH - w->w) / 2;
	w->y = y;
	w->h = 45;
	w->action = updateControls;

	cw = (ControlWidget *)w->data;
	cw->keyboard = app.config.keyControls[control];
	cw->joypad = app.config.joypadControls[control];
}

static void updateControls(void)
{
	Widget        *w;
	ControlWidget *cw;
	int            i;

	for (i = 0; i < CONTROL_MAX; i++)
	{
		w = getWidget(widgetNames[i], "controls");
		cw = (ControlWidget *)w->data;
		app.config.keyControls[i] = cw->keyboard;
		app.config.joypadControls[i] = cw->joypad;
	}
}

static void deadzone(void)
{
	SliderWidget *s;

	s = (SliderWidget *)deadzoneWidget->data;

	app.config.deadzone = (int)(DEADZONE_MAX * s->value);
}
