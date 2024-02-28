#ifndef TIMER_H
#define TIMER_H

#include  "raylib.h"

extern int timer;
extern bool isTimerRunning;

void StartTimer(void);
void StopTimer(void);
void TimerText(void);

#endif
