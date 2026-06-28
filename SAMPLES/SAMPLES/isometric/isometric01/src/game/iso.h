/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

void initISORender(void);
void doISOObjects(void);
void drawISOObjects(void);
void clearISOObjects(void);
void toISO(int x, int z, int *sx, int *sy);
void addISOObject(int x, int z, int sx, int sy, AtlasImage *texture);
