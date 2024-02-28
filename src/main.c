#include "raylib.h"
#include "../inc/screens.h"
#include "../inc/inventory.h"

enum GameScreen current_screen = MENU;
int exit_game = 0;

// global variables for inventory
Slot* inventory;
int new_slot_index = 1;

static void change_to_screen(enum GameScreen screen) {

    switch (current_screen) {
    case MENU:
        unload_menu_screen();
        break;
    case MENU_ABOUT:
        unload_about_screen();
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

    default:
        break;
    }
    current_screen = screen;
}

void update_draw_frame(void) {
    switch (current_screen) {
    case MENU:
        update_menu_screen();
        if (finish_menu_screen() == 1) {
            change_to_screen(MENU_ABOUT);
        }

        break;
    case MENU_ABOUT:
        update_about_screen();
        if (finish_about_screen() == 1) {
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
    default:
        break;
    }

    if (current_screen > MENU_ABOUT) { // inventory will be drawn only on our levels
        draw_inventory(inventory, new_slot_index);
    }
    EndDrawing();
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Title");
    init_menu_screen();
    inventory = create_inventory(); // creating inventory
    
    while (!WindowShouldClose()) {
        if (exit_game) {
            break;
        }

        handle_inventory_events(&new_slot_index); // handle inventory events
        update_draw_frame();
    }
    unload_inventory(); // unload inventory textures;
    CloseWindow();
}
