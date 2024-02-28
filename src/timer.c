#include "../inc/timer.h"

int timer = 300;
bool isTimerRunning = true;

void StartTimer(void)  {
    if (isTimerRunning && timer > 0) {
            timer--;
    }
}

void StopTimer(void) {
    isTimerRunning = false;
}

void TimerText(void)  {
    Color color = {215, 189, 91, 255};
    DrawText(TextFormat("Time left: %0.2d", timer), 100, 100, 20, color);
}
