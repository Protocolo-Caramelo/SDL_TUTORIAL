#ifndef INFOS_H
#define INFOS_H

#include"commons.h"
#include"ball/Ball.h"

#define INFOS_FONT_PATH "./assets/fonts/Ubuntu/Ubuntu-Regular.ttf"
#define INFOS_FONT_SIZE 24
#define INFOS_PADDINGCOLOR ((SDL_Color){255, 255, 255, 0})
#define INFOS_PADDING ((TextSpacing){0, 0, 0, 0, INFOS_PADDINGCOLOR})
#define INFOS_BORDERCOLOR ((SDL_Color){0, 0, 0, 255})
#define INFOS_BORDER ((TextSpacing){0, 0, 0, 0, INFOS_BORDERCOLOR})
#define INFOS_MARGINCOLOR ((SDL_Color){0, 0, 0, 255})
#define INFOS_MARGIN ((TextSpacing){0, 0, 0, 0, INFOS_MARGINCOLOR})

extern TextVTable InfosVTable;
extern TTF_Font* InfoFont;

/*
 */
typedef enum {
    OFF,
    ON,
} INFO_STATE;

/*
 * Show the fps in left top of screen
 */
#define INFO_FPS ON
#define INFO_FPS_X 0
#define INFO_FPS_Y 0
#define INFO_FPS_FONTCOLOR ((SDL_Color){0, 0, 0, 255})
#define INFO_FPS_FONTSIZE 1
#define INFO_FPS_FONTWRAP 0
#define INFO_FPS_MEM_SIZE 30
extern Text info_fps;
extern T_TIMESTAMP time_fps;
#define FPS_ITR_MAX 50
extern double fps;
extern uint16_t fps_itr;

/*
 * Show the count of balls and the max that can be spawed
 */
#define INFO_BALLSCOUNT ON
#define INFO_BALLSCOUNT_FONTCOLOR ((SDL_Color){0, 0, 0, 255})
#define INFO_BALLSCOUNT_FONTSIZE (5 / 8.0)
#define INFO_BALLSCOUNT_FONTWRAP 0
#define INFO_BALLSCOUNT_MEM_SIZE 30
extern Text info_ballsCount;

/*
 * Show a specific info of each ball
 */
#define INFO_BALL ON
// Ball's id
#define INFO_BALL_ID 0x1
// Ball's mass
#define INFO_BALL_MS 0x2
// Ball's radius
#define INFO_BALL_RD 0x4
// Ball's x position
#define INFO_BALL_PX 0x8
// Ball's y position
#define INFO_BALL_PY 0x10
// Ball's velocity x
#define INFO_BALL_VX 0x20
// Ball's velocity y
#define INFO_BALL_VY 0x40
// Ball's state
#define INFO_BALL_ST 0x80
// Ball's sin
#define INFO_BALL_SN 0x100
// Ball's cos
#define INFO_BALL_CS 0x200
// Ball's tan
#define INFO_BALL_TN 0x400
// Ball's angle in rad format
#define INFO_BALL_AR 0x800
// Ball's angle in deg format
#define INFO_BALL_AD 0x1000
// Ball's trajectory
#define INFO_BALL_TJ 0x2000
// The ball's infos will be showed just when the mouse is over the ball
#define INFO_BALL_SHOWED_WHEN_HIGHLIGHTED 0x4000
#define INFO_BALL_FONTCOLOR ((SDL_Color){0, 0, 0, 255})
#define INFO_BALL_FONTSIZE (1 / 2.0)
#define INFO_BALL_FONTWRAP 100
#define INFO_BALL_MEM_SIZE 50

extern uint64_t info_balls;

/*
 *
 */
void InfosVTable_init(Text*t);
void InfosVTable_exit(Text*t);
void InfosVTable_render(Text*t);
void InfosVTable_event(Text*t, SDL_Event);

void Infos_init();
void Infos_exit();
void Infos_render();
void Infos_event(SDL_Event);

void Infos_render_infoFPS();
void Infos_render_infoBallsCount();
void Infos_render_infoBall();

#endif
