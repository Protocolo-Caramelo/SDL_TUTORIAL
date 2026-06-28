/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

void prepareScene(void);
void presentScene(void);
void blit(SDL_Texture *texture, int x, int y, int center);
void blitScaled(SDL_Texture *texture, int x, int y, int w, int h);
void blitRotated(SDL_Texture *texture, int x, int y, int angle);
