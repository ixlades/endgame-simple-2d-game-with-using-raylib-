#include "../inc/items.h"
#include <math.h>
Texture item_card_tex;
Texture item_dwang_tex;
Texture item_screwdriver_tex;
Texture item_card_from_door_tex;

Item* create_items_in_room(enum GameScreen current_screen) {
	item_card_tex = LoadTexture("resource/Item_card.png");
	item_dwang_tex = LoadTexture("resource/Item_dwang.png");
	item_screwdriver_tex = LoadTexture("resource/item_screwdriver.png");

	if (current_screen == LEVEL_ONE) {
		Item* card = malloc(sizeof(Item)); // to unlock terminal
		card->pos_vec.x = 560;
		card->pos_vec.y = 560;
		card->type = CARD;
		card->isInInventory = false;
		card->isAvaiable = false;
		card->item_texture = item_card_tex;
		card->next = NULL;

		Item* dwang = malloc(sizeof(Item)); // to destroy box
		dwang->pos_vec.x = 750;
		dwang->pos_vec.y = 640;
		dwang->type = DWANG;
		dwang->isInInventory = false;
		dwang->isAvaiable = true;
		dwang->item_texture = item_dwang_tex;
		dwang->next = card;

		return dwang;
	}
	// 	if (current_screen == LEVEL_TWO) {
	// 	Item* screwdriver = malloc(sizeof(Item));
	// 	screwdriver->pos_vec.x = 550;
	// 	screwdriver->pos_vec.y = 620;
	// 	screwdriver->type = SCREWDRIVER;
	// 	screwdriver->isInInventory = false;
	// 	screwdriver->isAvaiable = false;
	// 	screwdriver->item_texture = item_screwdriver_tex;
	// 	screwdriver->next = NULL;

	// 	return screwdriver;
	// }
	return NULL;
}

void do_items(Item* items, Slot* inventory, Player protagonist, Window hint) {
	for (Item* curr_item = items; curr_item != NULL; curr_item = curr_item->next) {
		if ((fabsf(protagonist.pos.x + 64 - curr_item->pos_vec.x + 32) <= HERO_RANGE && (fabsf(protagonist.pos.y + 64 - curr_item->pos_vec.y + 32)) <= HERO_RANGE) && curr_item->isAvaiable == true && curr_item->isInInventory == false) {
			draw_hint_e(hint, curr_item->pos_vec.x, curr_item->pos_vec.y - 60);

			if (IsKeyPressed(KEY_E)) {
				if (curr_item->isAvaiable == true) {
					for (Slot* curr_slot = inventory; curr_slot != NULL; curr_slot = curr_slot->next) {
						if (curr_slot->item_type == EMPTY) {
							curr_item->isInInventory = true;

							curr_item->pos_vec.x = curr_slot->pos_vec.x - 4;
							curr_item->pos_vec.y = curr_slot->pos_vec.y;
							curr_slot->item_type = curr_item->type;
							curr_slot->item_texture = curr_item->item_texture;
							break;
						}
					}
				}
			}
		}

	}
}

void draw_items(Item* first_item) {
	for (Item* curr = first_item; curr != NULL; curr = curr->next) {
		if (!curr->isInInventory) {
			DrawTextureEx(curr->item_texture, curr->pos_vec, 0, ITEM_DEFAULT_SCALE, WHITE);
		}
	}
}

void free_items(Item *items) {
	Item* curr;
	while (items != NULL) {
		curr = items;
		items = items->next;
		free(curr);
	}
}

void unload_items() {
	UnloadTexture(item_card_tex);
	UnloadTexture(item_dwang_tex);
}
