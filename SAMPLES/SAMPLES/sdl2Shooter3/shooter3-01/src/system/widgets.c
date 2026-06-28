/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../json/cJSON.h"
#include "atlas.h"
#include "draw.h"
#include "lookup.h"
#include "text.h"
#include "util.h"
#include "widgets.h"

extern App app;

static Widget  widgetHead;
static Widget *widgetTail;
static void    createWidget(cJSON *root);
static void    createButtonWidget(Widget *w, cJSON *root);
static void    createSliderWidget(Widget *w, cJSON *root);
static void    createControlWidget(Widget *w, cJSON *root);
static void    createToggleWidget(Widget *w, cJSON *root);
static void    doControlWidget(void);
static void    drawButtonWidget(Widget *w);
static void    drawSliderWidget(Widget *w);
static void    drawControlWidget(Widget *w);
static void    drawToggleWidget(Widget *w);
static void    loadWidgets(char *filename);
static void    doMouse(char *groupName);

static double      sliderDelay;
static int         handleControlWidget;
static Widget     *hoverWidget;
static AtlasImage *buttonBackgroundTexture;

void initWidgets(void)
{
	memset(&widgetHead, 0, sizeof(Widget));
	widgetTail = &widgetHead;

	if (0) loadWidgets("data/widgets/stageOptions.json");

	buttonBackgroundTexture = getAtlasImage("gfx/ui/buttonBackground.png", 1);

	sliderDelay = 0;

	handleControlWidget = 0;
}

void doWidgets(char *groupName)
{
	sliderDelay = MAX(sliderDelay - app.deltaTime, 0);

	if (!handleControlWidget)
	{
		doMouse(groupName);
	}
	else
	{
		doControlWidget();
	}
}

static void doMouse(char *groupName)
{
	Widget       *w;
	ToggleWidget *t;
	SliderWidget *s;

	hoverWidget = NULL;

	for (w = widgetHead.next; w != NULL; w = w->next)
	{
		if (strcmp(w->groupName, groupName) == 0)
		{
			if (!w->hidden && !w->disabled && collision(app.mouse.x, app.mouse.y, 1, 1, w->x, w->y, w->w, w->h))
			{
				hoverWidget = w;

				if (app.mouse.buttons[SDL_BUTTON_LEFT])
				{
					if (w->type == WT_SLIDER)
					{
						s = (SliderWidget *)w->data;
						s->value = (1.0 * app.mouse.x - w->x) / w->w;

						if (s->value < 0.01)
						{
							s->value = 0;
						}

						if (s->value > 0.99)
						{
							s->value = 1;
						}
					}
					else if (w->type == WT_CONTROL)
					{
						app.activeWidget = w;

						app.lastKeyPressed = -1;

						app.lastButtonPressed = -1;

						handleControlWidget = 1;

						app.mouse.buttons[SDL_BUTTON_LEFT] = 0;
					}
					else
					{
						if (w->type == WT_TOGGLE)
						{
							t = (ToggleWidget *)w->data;
							t->on = !t->on;
						}

						app.mouse.buttons[SDL_BUTTON_LEFT] = 0;
					}

					if (w->type != WT_CONTROL)
					{
						w->action();
					}
				}
			}
		}
	}
}

static void doControlWidget(void)
{
	ControlWidget *cw;

	if (app.lastKeyPressed != -1 || app.lastButtonPressed != -1)
	{
		cw = (ControlWidget *)app.activeWidget->data;

		if (app.lastKeyPressed == SDL_SCANCODE_BACKSPACE)
		{
			cw->keyboard = 0;

			cw->joypad = -1;
		}
		else if (app.lastKeyPressed != SDL_SCANCODE_ESCAPE)
		{
			if (app.lastKeyPressed != -1)
			{
				cw->keyboard = app.lastKeyPressed;

				app.keyboard[app.lastKeyPressed] = 0;
			}

			if (app.lastButtonPressed != -1)
			{
				cw->joypad = app.lastButtonPressed;

				app.joypadButton[app.lastButtonPressed] = 0;
			}

			if (app.activeWidget->action != NULL)
			{
				app.activeWidget->action();
			}
		}

		handleControlWidget = 0;
	}
}

void drawWidgets(char *groupName)
{
	Widget *w;

	for (w = widgetHead.next; w != NULL; w = w->next)
	{
		if (!w->hidden && strcmp(w->groupName, groupName) == 0)
		{
			switch (w->type)
			{
				case WT_BUTTON:
					drawButtonWidget(w);
					break;

				case WT_SLIDER:
					drawSliderWidget(w);
					break;

				case WT_CONTROL:
					drawControlWidget(w);
					break;

				case WT_TOGGLE:
					drawToggleWidget(w);
					break;

				default:
					break;
			}
		}
	}
}

static void drawButtonWidget(Widget *w)
{
	SDL_Color backgroundColor, edgeColor;

	backgroundColor = ((ButtonWidget *)w->data)->color;

	if (w == hoverWidget)
	{
		backgroundColor.r *= 1.25;
		backgroundColor.g *= 1.25;
		backgroundColor.b *= 1.25;
	}

	edgeColor.r = backgroundColor.r * 0.5;
	edgeColor.g = backgroundColor.g * 0.5;
	edgeColor.b = backgroundColor.b * 0.5;

	app.fontScale = 1.5;

	drawRect(w->x, w->y, w->w, w->h, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
	drawRect(w->x, w->y, 2, w->h, edgeColor.r, edgeColor.g, edgeColor.b, 255);
	drawRect(w->x, w->y, w->w, 2, 255, 255, 255, 255);
	drawRect(w->x + w->w - 2, w->y, 2, w->h, 255, 255, 255, 255);
	drawRect(w->x, w->y + w->h - 2, w->w, 2, edgeColor.r, edgeColor.g, edgeColor.b, 255);

	SDL_SetTextureAlphaMod(buttonBackgroundTexture->texture, 96);
	blitAtlasImageScaled(buttonBackgroundTexture, w->x, w->y, w->w, w->h, 0);
	SDL_SetTextureAlphaMod(buttonBackgroundTexture->texture, 255);

	drawText(w->label, w->x + 18, w->y + 2, 0, 0, 0, TEXT_ALIGN_LEFT, 0);
	drawText(w->label, w->x + 16, w->y, 255, 255, 255, TEXT_ALIGN_LEFT, 0);

	if (w->disabled)
	{
		drawRect(w->x, w->y, w->w, w->h, 0, 0, 0, 192);
	}

	app.fontScale = 1;
}

static void drawSliderWidget(Widget *w)
{
	SliderWidget *s;

	s = (SliderWidget *)w->data;

	app.fontScale = 1.5;

	drawText(w->label, w->x - 25, w->y, 255, 255, 255, TEXT_ALIGN_RIGHT, 0);

	drawRect(w->x + 4, w->y + 4, (w->w - 8) * s->value, w->h - 8, 0, 192, 0, 255);

	drawOutlineRect(w->x, w->y, w->w, w->h, 255, 255, 255, 255);

	app.fontScale = 1;
}

static void drawControlWidget(Widget *w)
{
	SDL_Color      textColor;
	int            backgroundColor;
	ControlWidget *cw;
	char           text[32];

	cw = (ControlWidget *)w->data;

	textColor.r = textColor.g = textColor.b = 255;

	backgroundColor = 64;

	if (w == hoverWidget)
	{
		backgroundColor = 128;
	}

	if (w == app.activeWidget)
	{
		textColor.r = textColor.b = 0;
	}

	app.fontScale = 1.5;

	drawRect(w->x, w->y, w->w, w->h, 0, backgroundColor, 0, 128);
	drawOutlineRect(w->x, w->y, w->w, w->h, 0, backgroundColor, 0, 255);

	drawText(w->label, w->x + 20, w->y, textColor.r, textColor.g, textColor.b, TEXT_ALIGN_LEFT, 0);

	if (handleControlWidget && app.activeWidget == w)
	{
		sprintf(text, "...");
	}
	else
	{
		if (cw->keyboard != 0 && cw->joypad != -1)
		{
			sprintf(text, "%s or Btn %d", SDL_GetScancodeName(cw->keyboard), cw->joypad);
		}
		else if (cw->keyboard != 0)
		{
			sprintf(text, "%s", SDL_GetScancodeName(cw->keyboard));
		}
		else if (cw->joypad != -1)
		{
			sprintf(text, "Btn %d", cw->joypad);
		}
		else
		{
			sprintf(text, "N/A");
		}
	}

	drawText(text, w->x + w->w - 20, w->y, textColor.r, textColor.g, textColor.b, TEXT_ALIGN_RIGHT, 0);

	app.fontScale = 1;
}

static void drawToggleWidget(Widget *w)
{
	ToggleWidget *t;
	int           textCol, borderCol;

	t = (ToggleWidget *)w->data;

	app.fontScale = 1.5;

	textCol = 255;
	borderCol = 192;

	if (w->disabled)
	{
		textCol *= 0.25;
		borderCol *= 0.25;
	}

	drawText(w->label, w->x - 25, w->y, textCol, textCol, textCol, TEXT_ALIGN_RIGHT, 0);

	if (t->on)
	{
		drawRect(w->x + 4, w->y + 4, w->w - 8, w->h - 8, 0, borderCol, 0, 255);
	}

	drawOutlineRect(w->x, w->y, w->w, w->h, textCol, textCol, textCol, 255);

	app.fontScale = 1;
}

Widget *getWidget(char *name, char *groupName)
{
	Widget *w;

	for (w = widgetHead.next; w != NULL; w = w->next)
	{
		if (strcmp(w->name, name) == 0 && strcmp(w->groupName, groupName) == 0)
		{
			return w;
		}
	}

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "No such widget: name='%s', groupName='%s'", name, groupName);
	exit(1);

	return NULL;
}

static void loadWidgets(char *filename)
{
	cJSON *root, *node;
	char  *text;

	text = readFile(filename);

	root = cJSON_Parse(text);

	for (node = root->child; node != NULL; node = node->next)
	{
		createWidget(node);
	}

	cJSON_Delete(root);

	free(text);
}

static void createWidget(cJSON *root)
{
	Widget *w;
	int     type;

	type = lookup(cJSON_GetObjectItem(root, "type")->valuestring);

	if (type != -1)
	{
		w = malloc(sizeof(Widget));
		memset(w, 0, sizeof(Widget));
		widgetTail->next = w;
		w->prev = widgetTail;
		widgetTail = w;

		w->type = type;
		STRCPY(w->name, cJSON_GetObjectItem(root, "name")->valuestring);
		STRCPY(w->groupName, cJSON_GetObjectItem(root, "groupName")->valuestring);

		switch (w->type)
		{
			case WT_BUTTON:
				createButtonWidget(w, root);
				break;

			case WT_SLIDER:
				createSliderWidget(w, root);
				break;

			case WT_CONTROL:
				createControlWidget(w, root);
				break;

			case WT_TOGGLE:
				createToggleWidget(w, root);
				break;

			default:
				break;
		}
	}
}

static void createButtonWidget(Widget *w, cJSON *root)
{
	ButtonWidget *bw;
	int           r, g, b;

	STRCPY(w->label, cJSON_GetObjectItem(root, "label")->valuestring);

	bw = malloc(sizeof(ButtonWidget));
	memset(bw, 0, sizeof(ButtonWidget));
	w->data = bw;

	sscanf(cJSON_GetObjectItem(root, "color")->valuestring, "%d %d %d", &r, &g, &b);

	bw->color.r = r;
	bw->color.g = g;
	bw->color.b = b;

	app.fontScale = 1.5;

	calcTextDimensions(w->label, &w->w, &w->h);

	app.fontScale = 1;

	w->x -= 15;
	w->y -= 8;
	w->w += 30;
	w->h += 3;
}

static void createSliderWidget(Widget *w, cJSON *root)
{
	SliderWidget *s;

	STRCPY(w->label, cJSON_GetObjectItem(root, "label")->valuestring);

	s = malloc(sizeof(SliderWidget));
	memset(s, 0, sizeof(SliderWidget));
	w->data = s;

	w->w = 350;
	w->h = 45;
}

static void createControlWidget(Widget *w, cJSON *root)
{
	ControlWidget *c;

	STRCPY(w->label, cJSON_GetObjectItem(root, "label")->valuestring);

	c = malloc(sizeof(ControlWidget));
	memset(c, 0, sizeof(ControlWidget));
	w->data = c;
}

static void createToggleWidget(Widget *w, cJSON *root)
{
	ControlWidget *c;

	STRCPY(w->label, cJSON_GetObjectItem(root, "label")->valuestring);

	c = malloc(sizeof(ControlWidget));
	memset(c, 0, sizeof(ControlWidget));
	w->data = c;

	w->w = w->h = 45;
}
