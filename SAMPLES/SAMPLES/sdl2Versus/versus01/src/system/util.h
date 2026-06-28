/*
 * Copyright (C) 2024 Parallel Realities. All rights reserved.
 */

uint8_t collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
uint8_t pointInTriangle(double px, double py, double x1, double y1, double x2, double y2, double x3, double y3);
uint8_t lineLineCollision(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
uint8_t circleCircleCollision(int x1, int y1, int r1, int x2, int y2, int r2);
uint8_t lineCircleCollision(double x1, double y1, double x2, double y2, double cx, double cy, double r);
void    normalizeVector(int x1, int y1, int x2, int y2, double *dx, double *dy);
uint8_t fileExists(const char *filename);
FILE   *openFile(char *filename);
char   *readFile(char *filename);
uint8_t writeFile(const char *filename, const char *data);
void   *resize(void *array, int oldSize, int newSize);
void    hsvToRGB(double h, double s, double v, double *r, double *g, double *b);
