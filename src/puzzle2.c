#include "../inc/puzzle2.h"

Texture puzzle2_tex;

void init_puzzle2() {
	puzzle2_tex = LoadTexture("resource/note_puzzle2.png");
}

void do_puzzle2() {
	Vector2 note_pos;
	note_pos.x = (SCREEN_WIDTH / 2) - (NOTE_WIDTH * NOTE_SCALE) / 2;
	note_pos.y = (SCREEN_HEIGHT / 2) - (NOTE_HEIGHT * NOTE_SCALE) / 2;
	DrawTextureEx(puzzle2_tex, note_pos, 0, NOTE_SCALE, WHITE);
}
