#include <math.h>
#include "../inc/objects.h"
#include "../inc/window.h"

Texture box_tex;
Texture box_destroyed_tex;
Texture terminal_tex;
Texture terminal_unlocked_tex;
Texture note_tex;

int puzzle1_result;

Object* create_objects_in_room(enum GameScreen current_screen) {
	box_tex = LoadTexture("resource/box.png");
	box_destroyed_tex = LoadTexture("resource/box_destroyed.png");
	terminal_tex = LoadTexture("resource/terminal.png");
	terminal_unlocked_tex = LoadTexture("resource/terminal_unlocked.png");
	note_tex = LoadTexture("resource/note.png");
	

	if (current_screen == LEVEL_ONE) {
		Object* box = malloc(sizeof(Object));
		box->pos_vec.x = 550;
		box->pos_vec.y = 500;
		box->interaction_type = TO_DESTROY;
		box->isUnlocked = false;
		box->item_to_unlock = DWANG;
		box->puzzle_type = NONE;
		box->hidden_item = CARD;
		box->object_texture = box_tex;
		box->alternative_texture = box_destroyed_tex;
		box->next = NULL;
	
		Object* terminal = malloc(sizeof(Object));
		terminal->pos_vec.x = 1100;
		terminal->pos_vec.y = 550;
		terminal->interaction_type = TO_UNLOCK;
		terminal->isUnlocked = false;
		terminal->item_to_unlock = CARD;
		terminal->hidden_item = EMPTY;
		terminal->puzzle_type = PUZZZLE_1;
		terminal->is_puzzle_opened = false;
		terminal->object_texture = terminal_tex;
		terminal->alternative_texture = terminal_unlocked_tex;
		terminal->next = box;

		Object* note = malloc(sizeof(Object));
		note->pos_vec.x = 900;
		note->pos_vec.y = 470;
		note->interaction_type = TO_OPEN;
		note->isUnlocked = true;
		note->puzzle_type = PUZZLE_2;
		note->is_puzzle_opened = false;
		note->object_texture = note_tex;
		note->next = terminal;


		return note;
	}
	return NULL;
}

void do_objects(Object *objects, Player protagonist, Slot *inventory, int new_slot_index, Window hint, Item *items) {
	for (Object* curr_object = objects; curr_object != NULL; curr_object = curr_object->next) {
		if (fabsf((protagonist.pos.x + 64) - (curr_object->pos_vec.x + 64)) <= HERO_RANGE && (fabsf((protagonist.pos.y + 64) - (curr_object->pos_vec.y + 64)))) {
			for (Slot* curr_slot = inventory; curr_slot != NULL; curr_slot = curr_slot->next) {
				if (curr_slot->index == new_slot_index) {
					if (curr_object->interaction_type == TO_DESTROY && curr_object->item_to_unlock == curr_slot->item_type && curr_object->isUnlocked == false) {
						draw_hint_e(hint, curr_object->pos_vec.x + 32, curr_object->pos_vec.y - 60);

						if (IsKeyPressed(KEY_E)) {
							curr_object->object_texture = curr_object->alternative_texture;
							curr_object->isUnlocked = true;

							for (Item* curr_item = items; curr_item != NULL; curr_item = curr_item->next) {
								if (curr_object->hidden_item == curr_item->type) {
									curr_item->isAvaiable = true;
									break;
								}
							}
							break;
						}
					}
					if (curr_object->interaction_type == TO_UNLOCK && curr_object->item_to_unlock == curr_slot->item_type) {
						draw_hint_e(hint, curr_object->pos_vec.x, curr_object->pos_vec.y - 60);

						if (IsKeyPressed(KEY_E)) {
							curr_object->object_texture = curr_object->alternative_texture;
							curr_object->interaction_type = TO_OPEN;
							break;
						}
					}
					if (curr_object->interaction_type == TO_OPEN) {
						draw_hint_e(hint, curr_object->pos_vec.x, curr_object->pos_vec.y - 60);

						if (IsKeyPressed(KEY_E)) {
							if (curr_object->puzzle_type > NONE) {
								curr_object->is_puzzle_opened = true;
								break;
							}
						}
					}
				}
			}
		}

	}
}

void do_puzzles(Object *objects, Player protagonist) {
	for (Object* curr_object = objects; curr_object != NULL; curr_object = curr_object->next) {
		if (curr_object->is_puzzle_opened && fabsf((protagonist.pos.x + 64) - (curr_object->pos_vec.x + 64)) <= HERO_RANGE && (fabsf((protagonist.pos.y + 64) - (curr_object->pos_vec.y + 64)))) {
			if (curr_object->puzzle_type == PUZZZLE_1) {
				if (!IsKeyPressed(KEY_Q)) {
					puzzle1_result = do_puzzle1();
				}
				else {
					curr_object->is_puzzle_opened = false;
				}
				break;
			}
			if (curr_object->puzzle_type == PUZZLE_2) {
				if (!IsKeyPressed(KEY_Q)) {
					do_puzzle2();
				}
				else {
					curr_object->is_puzzle_opened = false;
				}
				break;
			}
		}
		else {
			curr_object->is_puzzle_opened = false;
		}

		if (puzzle1_result == 1){
			//smth
		}
		curr_object->is_puzzle_opened = false;
	}
}

void draw_objects(Object* first_object) {
	for (Object* curr = first_object; curr != NULL; curr = curr->next) {
		DrawTextureEx(curr->object_texture, curr->pos_vec, 0, 4, WHITE);
	}
}

void free_objects(Object* objects) {
	Object* curr;
	while (objects != NULL) {
		curr = objects;
		objects = objects->next;
		free(curr);
	}
}

void unload_objects() {
	UnloadTexture(box_tex);
	UnloadTexture(box_destroyed_tex);
	UnloadTexture(terminal_tex);
	UnloadTexture(terminal_unlocked_tex);
}
