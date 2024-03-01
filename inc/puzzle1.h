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

#define BUTTON_SIZE 60
#define BUTTON_MARGIN 20
#define BUTTONS_PER_ROW 5

#define CODE_LENGTH 10

void init_puzzle1(void);
int do_puzzle1(void);
