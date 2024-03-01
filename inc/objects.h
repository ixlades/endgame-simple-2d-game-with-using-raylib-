#pragma once

#include "raylib.h"
#include "../inc/common_enums.h"
#include "../inc/hints.h"
#include "../inc/screens.h"
#include "../inc/inventory.h"
#include "../inc/items.h"
#include "../inc/puzzle1.h"
#include "../inc/puzzle2.h"
#include "../inc/player.h"
#include "../inc/window.h"

#include "puzzle1.h"
#include "puzzle2.h"
#include "puzzle3.h"
#include "puzzle4.h"
#include <malloc.h>

#include "screens.h"

typedef struct s_object {
	Vector2 pos_vec;
	Texture object_texture;
	Texture alternative_texture;
	int interaction_type;
	int item_to_unlock;
	int puzzle_type;
	int is_puzzle_opened;
	int hidden_item;

	bool isUnlocked;

	struct s_object* next;
} Object;

void do_objects(Object* objects, Player protagonist, Slot* inventory, int new_slot_index, Window hint, Item* items);
Object* create_objects_in_room(enum GameScreen current_screen);
void draw_objects(Object* first_object);
void free_objects(Object* objects);
void unload_objects(void);
void do_puzzles(Object* objects, Player protagonist);
