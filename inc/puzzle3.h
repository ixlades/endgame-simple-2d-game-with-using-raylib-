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

#define NUM_IMAGES 15

#define IMAGE_WIDTH 50
#define IMAGE_HEIGHT 50

#define BUTTON_SIZE 60

void InitializeImages(void);
bool CheckOverlap(int index);
void init_puzzle3(void);
int do_puzzle3(void);
