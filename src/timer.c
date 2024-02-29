#include "raylib.h"

int timer = 3600;
bool isTimerRunning = true;

void StartTimer(void) {
    if (timer > 0) {
        timer--;
    }
}

void StopTimer(void) { 
    isTimerRunning = false;
}

void TimerText(void) {
    if (isTimerRunning)
    {
        Color color = {215, 189, 91, 255};
        DrawText(TextFormat("Time left: %0.2d", timer / 60), 100, 100, 20, color);
    }
    
}
