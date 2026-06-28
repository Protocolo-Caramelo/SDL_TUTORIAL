/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

unsigned long hashcode(const char *str);
int           collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
int           getDistance(int x1, int y1, int x2, int y2);
double        getAngle(int x1, int y1, int x2, int y2);
int           fileExists(const char *filename);
int           getFileModTime(const char *filename);
char		 *readFile(char *filename);
int           writeFile(const char *filename, const char *data);
void          calcSlope(int x1, int y1, int x2, int y2, double *dx, double *dy);
char		**toArray(char *in, int *count);
