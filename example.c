#include "inventory.h"

int main(void) {

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GAME");
	SetTargetFPS(60);

	Texture slot_texture;
	Texture slot_selected_texture;
	Slot* inventory = create_inventory(&slot_texture, &slot_selected_texture);
	int new_slot_index = 1;

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		handle_inventory_events(&new_slot_index);

		draw_inventory(inventory, new_slot_index, slot_texture, slot_selected_texture);

		EndDrawing();
	}
	return 0;
}
