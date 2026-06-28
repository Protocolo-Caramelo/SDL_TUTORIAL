/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

void         initTextures(void);
SDL_Texture *toTexture(SDL_Surface *surface, int destroySurface);
SDL_Texture *loadTexture(char *filename);
