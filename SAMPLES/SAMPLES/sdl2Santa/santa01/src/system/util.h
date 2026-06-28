/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

unsigned long hashcode(const char *str);
int           collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
char		 *readFile(char *filename);
void		 *resize(void *array, int oldSize, int newSize);
