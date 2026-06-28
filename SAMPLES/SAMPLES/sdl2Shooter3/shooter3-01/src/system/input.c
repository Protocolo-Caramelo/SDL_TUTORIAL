/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

extern App app;

static void doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 0;
	}
}

static void doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 1;

		app.lastKeyPressed = event->keysym.scancode;
	}
}

static void doMouseDown(SDL_MouseButtonEvent *event)
{
	if (event->button >= 0 && event->button < MAX_MOUSE_BUTTONS)
	{
		app.mouse.buttons[event->button] = 1;
	}
}

static void doMouseUp(SDL_MouseButtonEvent *event)
{
	if (event->button >= 0 && event->button < MAX_MOUSE_BUTTONS)
	{
		app.mouse.buttons[event->button] = 0;
	}
}

static void doButtonDown(SDL_JoyButtonEvent *event)
{
	if (event->state == SDL_PRESSED && event->button < MAX_JOYPAD_BUTTONS)
	{
		app.joypadButton[event->button] = 1;

		app.lastButtonPressed = event->button;
	}
}

static void doButtonUp(SDL_JoyButtonEvent *event)
{
	if (event->state == SDL_RELEASED && event->button < MAX_JOYPAD_BUTTONS)
	{
		app.joypadButton[event->button] = 0;
	}
}

static void doJoyAxis(SDL_JoyAxisEvent *event)
{
	if (event->axis < JOYPAD_AXIS_MAX)
	{
		app.joypadAxis[event->axis] = event->value;
	}
}

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;

			case SDL_MOUSEBUTTONDOWN:
				doMouseDown(&event.button);
				break;

			case SDL_MOUSEBUTTONUP:
				doMouseUp(&event.button);
				break;

			case SDL_JOYBUTTONDOWN:
				doButtonDown(&event.jbutton);
				break;

			case SDL_JOYBUTTONUP:
				doButtonUp(&event.jbutton);
				break;

			case SDL_JOYAXISMOTION:
				doJoyAxis(&event.jaxis);
				break;

			default:
				break;
		}
	}

	SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
}

void clearInput(void)
{
	SDL_Event event;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	memset(app.mouse.buttons, 0, sizeof(int) * MAX_MOUSE_BUTTONS);

	while (SDL_PollEvent(&event))
	{
	}
}
