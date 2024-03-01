#include <math.h>
#include "../inc/objects.h"
#include "../inc/window.h"

Texture box_tex;
Texture box_destroyed_tex;
Texture terminal_tex;
Texture terminal_unlocked_tex;
Texture note_tex;
Texture computer_tex;
Texture computer_unlocked_tex;
Texture panel_tex;
Texture hide_tex;
Texture safe_tex;

int puzzle1_result;
int puzzle3_result;
int puzzle4_result;

Object* create_objects_in_room(enum GameScreen current_screen) {
	box_tex = LoadTexture("resource/box.png");
	box_destroyed_tex = LoadTexture("resource/box_destroyed.png");
	terminal_tex = LoadTexture("resource/terminal.png");
	terminal_unlocked_tex = LoadTexture("resource/terminal_unlocked.png");
	note_tex = LoadTexture("resource/note.png");
	computer_tex = LoadTexture("resource/computer.png");
	computer_unlocked_tex = LoadTexture("resource/computer_unlocked.png");
	panel_tex = LoadTexture("resource/panel.png");
	hide_tex = LoadTexture("resource/hide.png");
	

	if (current_screen == LEVEL_ONE) {
		Object* box = malloc(sizeof(Object));
		box->pos_vec.x = 525;
		box->pos_vec.y = 519;
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
		terminal->pos_vec.y = 480;
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
		note->pos_vec.x = 850;
		note->pos_vec.y = 490;
		note->interaction_type = TO_OPEN;
		note->isUnlocked = true;
		note->puzzle_type = PUZZLE_2;
		note->is_puzzle_opened = false;
		note->object_texture = note_tex;
		note->next = terminal;

		return note;
	}
	if (current_screen == LEVEL_TWO) {

		Object* computer = malloc(sizeof(Object));
		computer->pos_vec.x = 45;
		computer->pos_vec.y = 159;
		computer->interaction_type = TO_OPEN;
		computer->isUnlocked = true;
		computer->puzzle_type = PUZZLE_3;
		computer->is_puzzle_opened = false;
		computer->object_texture = computer_tex;
		computer->alternative_texture = computer_unlocked_tex;
		computer->next = NULL;

		Object* panel = malloc(sizeof(Object));
		panel->pos_vec.x = 900;
		panel->pos_vec.y = 540;
		panel->interaction_type = TO_OPEN;
		panel->isUnlocked = true;
		panel->puzzle_type = PUZZLE_4;
		panel->is_puzzle_opened = false;
		panel->object_texture = panel_tex;
		panel->alternative_texture = panel_tex;
		panel->next = computer;

		// Object* box_2 = malloc(sizeof(Object));
		// box_2->pos_vec.x = 500;
		// box_2->pos_vec.y = 540;
		// box_2->interaction_type = TO_DESTROY;
		// box_2->isUnlocked = false;
		// box_2->item_to_unlock = DWANG;
		// box_2->puzzle_type = NONE;
		// box_2->hidden_item = SCREWDRIVER;
		// box_2->object_texture = box_tex;
		// box_2->alternative_texture = box_destroyed_tex;
		// box_2->next = panel;

		Object* hide = malloc(sizeof(Object));
		hide->pos_vec.x = 1170;
		hide->pos_vec.y = 600;
		hide->interaction_type = TO_DESTROY;
		hide->isUnlocked = false;
		hide->item_to_unlock = SCREWDRIVER;
		hide->puzzle_type = NONE;
		hide->hidden_item = CARD_FROM_DOOR;
		hide->object_texture = hide_tex;
		hide->alternative_texture = hide_tex;
		hide->next = panel;

		return hide;
	}
	return NULL;
}

void do_objects(Object *objects, Player protagonist, Slot *inventory, int new_slot_index, Window hint, Item *items) {
	for (Object* curr_object = objects; curr_object != NULL; curr_object = curr_object->next) {
		if (fabsf((protagonist.pos.x + 64) - (curr_object->pos_vec.x + 64)) <= HERO_RANGE && (fabsf((protagonist.pos.y + 64) - (curr_object->pos_vec.y + 64)) <= HERO_RANGE)) {
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
		if (curr_object->is_puzzle_opened && fabsf((protagonist.pos.x + 64) - (curr_object->pos_vec.x + 64)) <= HERO_RANGE && (fabsf((protagonist.pos.y + 64) - (curr_object->pos_vec.y + 64)) <= HERO_RANGE)) {
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
			if (curr_object->puzzle_type == PUZZLE_3) {
				if (!IsKeyPressed(KEY_Q)) {
					puzzle3_result = do_puzzle3();
				}
				else {
					curr_object->is_puzzle_opened = false;
				}
				break;
			}
			if (curr_object->puzzle_type == PUZZLE_4) {
				if (!IsKeyPressed(KEY_Q)) {
					puzzle4_result = do_puzzle4();
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
			check_puzzle_completion_lvl1(puzzle1_result);
		}
		
		if (puzzle3_result == 1 && puzzle4_result == 1) {
			isAllMissionDone(puzzle3_result == 1 && puzzle4_result == 1);
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
