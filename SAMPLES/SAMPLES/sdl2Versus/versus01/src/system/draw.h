/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

void initDraw(void);
void prepareScene(void);
void presentScene(void);
void blit(SDL_Texture *texture, int x, int y, int center, SDL_RendererFlip flip);
void drawRect(int x, int y, int w, int h, int r, int g, int b, int a);
void drawOutlineRect(int x, int y, int w, int h, int r, int g, int b, int a);
void drawLine(double x1, double y1, double x2, double y2, int r, int g, int b, int a);
void drawVertex(SDL_Vertex *v);
void flushGeometry(void);
