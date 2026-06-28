/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/text.h"
#include "hud.h"

void drawHud(void)
{
	drawText("Score: 0", 10, 0, 255, 255, 255, TEXT_ALIGN_LEFT, 0);

	drawText("Highscore: 0", SCREEN_WIDTH - 10, 0, 255, 255, 255, TEXT_ALIGN_RIGHT, 0);
}
