/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "game.h"

extern Game game;

void initGame(void)
{
	memset(&game, 0, sizeof(Game));
}
