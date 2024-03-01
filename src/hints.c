#include "../inc/hints.h"

Texture hint_e_tex;

Window create_hint(void) {

	hint_e_tex = LoadTexture("resource/hint_E.png");
	Window hint_e;
	hint_e.window_texture = hint_e_tex;
	return hint_e;
}

void draw_hint_e(Window hint, int x, int y) {
	hint.pos_vec.x = x;
	hint.pos_vec.y = y;

	DrawTextureEx(hint.window_texture, hint.pos_vec, 0, 4, WHITE);
}
