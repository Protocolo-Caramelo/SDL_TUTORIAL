/*
 * Copyright (C) 2025 Parallel Realities. All rights reserved.
 */

void          initUtils(void);
void          expireStrings(void);
unsigned long hashcode(const char *str);
char		 *readFile(char *filename);
int           collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
int           getDistance(int x1, int y1, int x2, int y2);
void          hsvToRGB(double h, double s, double v, double *r, double *g, double *b);
char		 *formattedString(const char *format, ...);
char		 *expiringFormattedString(const char *format, ...);
