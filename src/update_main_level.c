#include "../inc/main_level.h"

void update_main_level(void) {
    movement(&characer, &stock);
    for (int i = 0; i < NUM_OF_PLATFORMS; ++i) {
        Jump(&characer, &stock, &platforms[i]);
    }
}
