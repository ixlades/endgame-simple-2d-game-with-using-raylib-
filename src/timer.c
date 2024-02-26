#include "timer.h"

int timer = 3600;

void startTimer(void)  {
    if (timer > 0) {
            timer--;
        }
}

void timerText(void)  {
    DrawText(TextFormat("Time left: %0.2d", timer), 10, 10, 20, WHITE);
}

