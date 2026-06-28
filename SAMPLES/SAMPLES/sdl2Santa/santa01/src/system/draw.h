/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

void prepareScene(void);
void presentScene(void);
void blit(SDL_Texture *texture, int x, int y, int center, SDL_RendererFlip flip);
void blitAtlasImage(AtlasImage *atlasImage, int x, int y, int center, SDL_RendererFlip flip);
void drawRect(int x, int y, int w, int h, int r, int g, int b, int a);
void drawOutlineRect(int x, int y, int w, int h, int r, int g, int b, int a);
