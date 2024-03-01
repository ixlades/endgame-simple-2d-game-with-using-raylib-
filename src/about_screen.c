#include "raylib.h"
#include "../inc/screens.h"

int font_size_about = 24;
static int finish_abt_screen = 0;
float roundness_about = 0.5f;
float thickness_about = 3.0f;
Button back_to_menu = {.text = "Back"};
Image about_bg;
Texture2D about_texture;

void init_about_screen(void) {
    about_bg = LoadImage("resource/menu_background.png");
    about_texture = LoadTextureFromImage(about_bg);
    back_to_menu.rect = (Rectangle){GetScreenWidth() / 2 - 50, GetScreenHeight() - 70, 100, 50};
    back_to_menu.color = RED;
    finish_abt_screen = 0;
}

void update_about_screen(void) {
    if (CheckCollisionPointRec(GetMousePosition(), back_to_menu.rect)) {
        back_to_menu.color = BLUE;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            finish_abt_screen = 1;
        }
    } else {
        back_to_menu.color = RED;
    }
}

void draw_about_screen(void) {
    DrawTexture(about_texture, 0, 0, RAYWHITE);
    DrawRectangleRounded(back_to_menu.rect, roundness_about, 0.0f,
                         back_to_menu.color);
    DrawRectangleRoundedLines(back_to_menu.rect, roundness_about, 0.0f,
                              thickness_about, PINK);
    DrawText(back_to_menu.text,
             back_to_menu.rect.x + back_to_menu.rect.width / 2 -
                 MeasureText(back_to_menu.text, font_size_about) / 2,
             back_to_menu.rect.y + back_to_menu.rect.height / 2 -
                 font_size_about / 2,
             font_size_about, BLACK);
    DrawText("Our team", GetScreenWidth() / 2 - 70, GetScreenHeight() / 8,
             font_size_about + 12, RED);

    DrawText("kaplanich:", GetScreenWidth() / 2 - 42,
             (float)GetScreenHeight() / 8 + 80, font_size_about, (Color){180, 169, 175, 255});
    DrawText("andromeda:", GetScreenWidth() / 2 - 42,
             (float)GetScreenHeight() / 8 + (80 * 2), font_size_about, (Color){180, 169, 175, 255});
    DrawText("devitfro:", GetScreenWidth() / 2 - 42,
             (float)GetScreenHeight() / 8 + (80 * 3), font_size_about, (Color){180, 169, 175, 255});
    DrawText("heo1wayy:", GetScreenWidth() / 2 - 42,
             (float)GetScreenHeight() / 8 + (80 * 4), font_size_about, (Color){180, 169, 175, 255});
    DrawText("chorv:", GetScreenWidth() / 2 - 42,
             (float)GetScreenHeight() / 8 + (80 * 5), font_size_about, (Color){180, 169, 175, 255});
    DrawText("ixlades:", GetScreenWidth() / 2 - 42,
             (float)GetScreenHeight() / 8 + (80 * 6), font_size_about, (Color){180, 169, 175, 255});
}

void unload_about_screen(void) {
    UnloadTexture(about_texture);
    UnloadImage(about_bg);
}

int finish_about_screen(void) { 
    return finish_abt_screen;
}
