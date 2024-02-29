#pragma once

#define SLOT_SCALE 3
#define FIRST_SLOT_X (SCREEN_WIDTH - 288 * SLOT_SCALE)/2

typedef struct s_slot {
	Vector2 pos_vec;
	Texture slot_texture;
	int index;
	int item_type;
	Texture item_texture; ///

	struct s_slot* next;
} Slot;

Slot* create_inventory();
void handle_inventory_events(int* new_slot_index);
void draw_inventory(Slot* first_slot, int new_slot_index);
void unload_inventory();
