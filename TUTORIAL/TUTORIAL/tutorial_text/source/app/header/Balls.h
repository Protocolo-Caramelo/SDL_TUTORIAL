#ifndef BALLS_H
#define BALLS_H

#include"ball/Football.h"
#include"ball/Basketball.h"
#include"ball/Tennis.h"
#include"ball/PingPong.h"

/*
 * General functions for all balls
 */
void Balls_init();
void Balls_exit();
void Balls_render();
void Balls_event(SDL_Event);

#endif
