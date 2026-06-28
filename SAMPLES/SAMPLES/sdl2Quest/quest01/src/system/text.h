/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

void         initFonts(void);
SDL_Texture *getTextTexture(char *text, int type);
void         drawShadowText(char *text, int x, int y, int r, int g, int b, int align);
void         drawText(char *text, int x, int y, int r, int g, int b, int align, int maxWidth);
void         calcTextDimensions(char *text, int *w, int *h);
int          getWrappedTextHeight(char *text, int maxWidth);
