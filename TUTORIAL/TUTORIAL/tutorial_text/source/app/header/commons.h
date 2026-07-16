#ifndef COMMUNS_H
#define COMMUNS_H

#include<graphical.h>
#include<stdint.h>
#include<math.h>

typedef double T_COL;
typedef double T_ROW;
typedef int16_t T_COLINT;
typedef int16_t T_ROWINT;

typedef uint16_t T_WIDTH;
typedef uint16_t T_HEIGHT;
typedef double T_WEIGHT;

typedef uint64_t T_TIMESTAMP;

#define SDL_DELAY 16 // ms

#define RAD_TO_DEG(a) (a * 180 / M_PI)
#define DEG_TO_RAG(a) (a * M_PI / 180)

/*
 * App
 */
#define APP_INIT_WINDOW_NAME "Tutorial text"
#define APP_INIT_WINDOW_XPOS SDL_WINDOWPOS_UNDEFINED
#define APP_INIT_WINDOW_YPOS SDL_WINDOWPOS_UNDEFINED
#define APP_INIT_WINDOW_WIDTH 900
#define APP_INIT_WINDOW_HEIGHT 450
#define APP_INIT_WINDOW_FLAGS (SDL_WINDOW_RESIZABLE)
#define APP_INIT_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED)

/*
 * Physics important values
 */
#define G_FORCE 9.8 // ms/s^2
#define FRICTION_VAL 0.2
#define FRICTION_ELASTIC_VAL 0.8
#define DELTATIME (16 / 60)
#define COLISION_ELASTIC_VAL 1

#define SIMULATION_ITR_MAX 30

/*
 * Ball
 */
#define BALLS_AMT 25

// Ball's texture path
#define FOOTBALL_TEXTURE_PATH "./assets/football.png"
#define BASKETBALL_TEXTURE_PATH "./assets/basketball.png"
#define TENNIS_TEXTURE_PATH "./assets/tennis.png"
#define PINGPONG_TEXTURE_PATH "./assets/pingpong.png"

// Ball's width(pxls)
#define FOOTBALL_TEXTURE_WIDTH 100 // 22cm
#define BASKETBALL_TEXTURE_WIDTH 109 // 24cm
#define TENNIS_TEXTURE_WIDTH 31 // 6.86cm
#define PINGPONG_TEXTURE_WIDTH 18 // 4cm

// Balls's radius
#define FOOTBALL_RADIUS (FOOTBALL_TEXTURE_WIDTH / 2)
#define BASKETBALL_RADIUS (BASKETBALL_TEXTURE_WIDTH / 2)
#define TENNIS_RADIUS (TENNIS_TEXTURE_WIDTH / 2)
#define PINGPONG_RADIUS (PINGPONG_TEXTURE_WIDTH / 2)

// Ball's weight(kg)
#define FOOTBALL_WEIGHT 0.450
#define BASKETBALL_WEIGHT 0.650
#define TENNIS_WEIGHT 0.060
#define PINGPONG_WEIGHT 0.003


#endif
