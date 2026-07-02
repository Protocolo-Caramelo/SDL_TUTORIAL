#ifndef APP_H
#define APP_H

#include<graphical_win.h>
#include<time.h>

extern Win app;
void App_set_color(Win*);
void App_events(Win*);
void App_present(Win*);

void doApp();

#endif
