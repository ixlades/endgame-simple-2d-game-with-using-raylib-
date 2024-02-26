#pragma once

#include "raylib.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SLOT_SCALE 3
#define FIRST_SLOT_X (SCREEN_WIDTH - 288 * SLOT_SCALE)/2

enum item_type {
	EMPTY,
	KEY,
	CARD
};

typedef struct s_slot {
	Vector2 pos_vec;
	Texture slot_texture;
	int index;
	int item_type;

	struct s_slot* next;
} Slot;

typedef struct {
	Vector2 pos_vec;
	Texture item_texture;
	bool isInInventory;
	int type;
} Item;

Slot* create_inventory(Texture* slot_texture, Texture* slot_selected_tex);
void handle_inventory_events(int* new_slot_index);
void draw_inventory(Slot* first_slot, int new_slot_index, Texture slot_texture, Texture slot_selected_tex);
