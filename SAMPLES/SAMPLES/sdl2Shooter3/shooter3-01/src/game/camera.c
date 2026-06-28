/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "camera.h"

extern App   app;
extern Stage stage;

void doCamera(void)
{
	stage.camera.x = stage.player->x;
	stage.camera.y = stage.player->y;

	stage.camera.x -= SCREEN_WIDTH / 2;
	stage.camera.y -= SCREEN_HEIGHT / 2;
}
