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

#define ITEM_DEFAULT_SCALE 4

typedef struct s_item {
	Vector2 pos_vec;
	Texture item_texture;
	int type;

	bool isInInventory;
	bool isAvaiable;

	struct s_item* next;
} Item;

Item* create_items_in_room(enum GameScreen current_screen);
void do_items(Item* items, Slot* inventory, Player protagonist, Window hint);
void draw_items(Item* first_item);
void free_items(Item* items);
void unload_items();
