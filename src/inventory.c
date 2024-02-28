#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include "../inc/screens.h"
#include "../inc/inventory.h"

Texture slot_texture;
Texture slot_selected_texture;

Slot* create_inventory() {
	slot_texture = LoadTexture("../resource/slot.png");
	slot_selected_texture = LoadTexture("../resource/slot_selected.png");

	Slot* first_slot = malloc(sizeof(Slot));

	first_slot->pos_vec.x = FIRST_SLOT_X;
	first_slot->pos_vec.y = 0;
	first_slot->slot_texture = slot_texture;
	first_slot->index = 1;
	first_slot->item_type = EMPTY;
	first_slot->next = NULL;

	int j = 32 * SLOT_SCALE;
	int k = 2;
	Slot* curr = first_slot;
	for (int i = 1; i < 9; i++) {
		Slot* new_slot = malloc(sizeof(Slot));
		new_slot->pos_vec.x = FIRST_SLOT_X + j;
		new_slot->pos_vec.y = 0;
		new_slot->index = k;
		new_slot->item_type = EMPTY;
		new_slot->slot_texture = slot_texture;
		new_slot->next = NULL;

		curr->next = new_slot;
		curr = curr->next;
		j += 32 * SLOT_SCALE;
		k++;
	}

	return first_slot;
}


void handle_inventory_events(int* new_slot_index) {

	if (IsKeyPressed(KEY_ONE)) {
		*new_slot_index = 1;
	}
	if (IsKeyPressed(KEY_TWO)) {
		*new_slot_index = 2;
	}
	if (IsKeyPressed(KEY_THREE)) {
		*new_slot_index = 3;
	}
	if (IsKeyPressed(KEY_FOUR)) {
		*new_slot_index = 4;
	}
	if (IsKeyPressed(KEY_FIVE)) {
		*new_slot_index = 5;
	}
	if (IsKeyPressed(KEY_SIX)) {
		*new_slot_index = 6;
	}
	if (IsKeyPressed(KEY_SEVEN)) {
		*new_slot_index = 7;
	}
	if (IsKeyPressed(KEY_EIGHT)) {
		*new_slot_index = 8;
	}
	if (IsKeyPressed(KEY_NINE)) {
		*new_slot_index = 9;
	}
}

void draw_inventory(Slot* first_slot, int new_slot_index) {
	for (Slot* curr = first_slot; curr != NULL; curr = curr->next) {
		if (curr->index == new_slot_index) {
			curr->slot_texture = slot_selected_texture;
		}
		else {
			curr->slot_texture = slot_texture;
		}
		DrawTextureEx(curr->slot_texture, curr->pos_vec, 0, SLOT_SCALE, WHITE);
	}
}

void unload_inventory() {
	UnloadTexture(slot_texture);
	UnloadTexture(slot_selected_texture);
}
