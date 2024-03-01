#include "raylib.h"
#include "../inc/common_enums.h"
#include "../inc/hints.h"
#include "../inc/screens.h"
#include "../inc/inventory.h"
#include "../inc/items.h"
#include "../inc/objects.h"
#include "../inc/puzzle1.h"
#include "../inc/puzzle2.h"
#include "../inc/player.h"
#include "../inc/window.h"
// #include "../inc/finish.h"
#include "../inc/timer.h"
//#include "../inc/main_level.h"
#include "../inc/puzzle3.h"
#include "../inc/puzzle4.h"
// #include "../inc/main_level.h"

enum GameScreen current_screen = MENU;
int exit_game = 0;
// global variables for inventory
Slot* inventory;
int new_slot_index = 1;

// global vars for items and objects
Item* items;
Object* objects;

// Global variable for hint
Window hint;

// player is obligated for some functions
Player player;

static void change_to_screen(enum GameScreen screen) {

    switch (current_screen) {
    case MENU:
        unload_menu_screen();
        break;
    case MENU_ABOUT:
        unload_about_screen();
        break;
    case LEVEL_ONE:
        unload_level1_screen();
        break;
    case LEVEL_TWO:
        unload_main_level();
        break;
    case LEVEL_THREE:
        unload_finish_screen();
        break;
    default:
        break;
    }
    switch (screen) {
    case MENU:
        init_menu_screen();
        break;
    case MENU_ABOUT:
        init_about_screen();
        break;
    case LEVEL_ONE:
        init_level1_screen();
        break;
    case LEVEL_TWO:
        init_main_level();
        break;
    case LEVEL_THREE:
        init_finish_screen();
        break;
    default:
        break;
    }
    free_items(items); // free previous items
    free_objects(objects); // free previous objects
    current_screen = screen;
    items = create_items_in_room(current_screen); // creating new items
    objects = create_objects_in_room(current_screen); // creating new items
}

void update_draw_frame(void) {
    switch (current_screen) {
    case MENU:
        update_menu_screen();
        if (finish_menu_screen() == 1) {
            change_to_screen(MENU_ABOUT);
            break;
        }
        if (finish_menu_screen() == 2) {
            change_to_screen(LEVEL_ONE);
            break;
        }
        break;
    case MENU_ABOUT:
        update_about_screen();
        if (finish_about_screen() == 1) {
            change_to_screen(MENU);
        }
        break;
    case LEVEL_ONE:
        update_level1_screen();
        if (finish_level1_screen() == 1) {
            change_to_screen(LEVEL_TWO);
        }
        break;
    case LEVEL_TWO:
        update_main_level();
        if (isDoorUnlock()) {
            change_to_screen(LEVEL_THREE);
        }
        break;
    case LEVEL_THREE:
        update_finish_screen();
        if (finish_last_screen() == 1) {
            change_to_screen(MENU);
        }
        break;
    default:
        break;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (current_screen) {
    case MENU:
        draw_menu_screen();
        break;
    case MENU_ABOUT:
        draw_about_screen();
        break;
    case LEVEL_ONE:
        draw_level1_screen();
        break;
    case LEVEL_TWO:
        draw_main_level();
        break;
    case LEVEL_THREE:
        draw_finish_screen();
        break;
    default:
        break;
    }

     // draw items and objects if they exist in room
    if (items != NULL) {
        draw_items(items);
    }
    if (objects != NULL) {
        draw_objects(objects);
    }
    do_items(items, inventory, player, hint); // doing items logic
    do_objects(objects, player, inventory, new_slot_index, hint, items); // doing objects logic
    do_puzzles(objects, player); // doing puzzles

    if (current_screen == LEVEL_ONE) {
        draw_player();
    }
    if (current_screen == LEVEL_TWO) {
        draw_player_lvl2();
    }  
    if (current_screen > MENU_ABOUT) { // inventory will be drawn only on our levels
        draw_inventory(inventory, new_slot_index);

   }
   EndDrawing();
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Title");
    SetTargetFPS(60);
    init_menu_screen();
    inventory = create_inventory(); // creating inventory
    items = create_items_in_room(current_screen); // creating items
    objects = create_objects_in_room(current_screen); // creating objects
    hint = create_hint(); // creating hint_e

    // initializing puzzles
    init_puzzle1();
    init_puzzle2();
    init_puzzle3();
    init_puzzle4();
    
    while (!WindowShouldClose()) {
        if (exit_game) {
            break;
        }

        handle_inventory_events(&new_slot_index); // handle inventory events
        update_draw_frame();
    }
    unload_inventory(); // unload inventory textures;
    unload_items(); // unload items textures
    unload_objects(); // unload objects textures
    CloseWindow();
}
