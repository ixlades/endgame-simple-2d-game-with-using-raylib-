#include "../inc/main_level.h"

void draw_platforms(void) {
    for (int i = 0; i < NUM_OF_PLATFORMS; ++i) {
        DrawTexture(platformTexture, platforms[i].x, platforms[i].y, WHITE);
    }
}

void draw_main_level(void) {
    DrawTexture(main_bg, 0, 0, WHITE);
    draw_platforms();
    DrawTexture(characterTexture, characer.x, characer.y, WHITE);
}