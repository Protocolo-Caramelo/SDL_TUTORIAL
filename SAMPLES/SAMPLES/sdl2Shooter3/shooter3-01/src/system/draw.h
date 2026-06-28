/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

void initDraw(void);
void prepareScene(void);
void presentScene(void);
void blit(SDL_Texture *texture, int x, int y, int center, SDL_RendererFlip flip);
void blitAtlasImage(AtlasImage *atlasImage, int x, int y, int center, SDL_RendererFlip flip);
void blitAtlasImageScaled(AtlasImage *atlasImage, int x, int y, int w, int h, int center);
void blitRotated(AtlasImage *atlasImage, int x, int y, double angle);
void drawRect(int x, int y, int w, int h, int r, int g, int b, int a);
void drawOutlineRect(int x, int y, int w, int h, int r, int g, int b, int a);
void drawCircle(int cx, int cy, int radius, int r, int g, int b, int a);
void doBackground(double x, double y);
void drawBackground(SDL_Texture *texture);
