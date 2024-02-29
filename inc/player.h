#pragma once

#include "raylib.h"

#define HERO_RANGE 80

typedef struct s_player {
    Texture2D texture;
    Vector2 pos;
    int direction;
    bool isWalking;
} Player;
