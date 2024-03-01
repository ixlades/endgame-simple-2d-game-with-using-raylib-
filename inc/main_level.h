#ifndef MAIN_LEVEL_H
#define MAIN_LEVEL_H

#include "movement.h"
#include "screens.h"
#include "hints.h"

Texture2D main_bg;
Texture2D platformTexture;
Texture2D characterTexture;

Rectangle platforms[NUM_OF_PLATFORMS];
Rectangle characer;

SizeData stock;

void init_main_level(void);
void draw_platforms(void);
void draw_main_level(void);
void draw_player_lvl2(void);
void update_main_level(void);
void unload_main_level(void);
bool isAllMissionDone(int result);

#endif
