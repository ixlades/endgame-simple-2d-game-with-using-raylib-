#pragma once

#include "raylib.h"
#include "common_enums.h"
#include "hints.h"
#include "inventory.h"
#include "items.h"
#include "window.h"
#include "player.h"
#include "screens.h"
#include "stdlib.h"
#include <stdbool.h>

#define MAX_IMAGES 4
#define NUM_TARGET_POINTS 4

typedef struct {
    Vector2 position;
    int right_target_index;
    Texture2D texture;
    bool isDragging;
    float scale;
} ImageInfo;

void init_puzzle4();
void update_puzzle4();
void draw_puzzle4();
int do_puzzle4();
