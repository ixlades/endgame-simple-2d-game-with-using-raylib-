#include "raylib.h"
#include <stdio.h>
#include "../inc/screens.h"

Button play_button = {.text = "Play"};
Button exit_button = {.text = "Exit"};
Button about_button = {.text = "About"};
Image menu_bg;
Texture2D menu_texture;
int font_size_menu = 24;
static int finish_mnu_screen = 0;
float roundness_menu = 0.5f;
float thickness_menu = 3.0f;

void init_menu_screen(void)
{
    menu_bg = LoadImage("resource/menu_background.png");
    menu_texture = LoadTextureFromImage(menu_bg);
    play_button.rect = (Rectangle){GetScreenWidth() / 2 - 50, GetScreenHeight() / 4 - 50, 100, 50};
    play_button.color = RED;
    exit_button.rect = (Rectangle){GetScreenWidth() / 2 - 50, GetScreenHeight() / 4 + 150, 100, 50};
    exit_button.color = RED;
    about_button.rect = (Rectangle){GetScreenWidth() / 2 - 50, GetScreenHeight() / 4 + 50, 100, 50};
    about_button.color = RED;
    finish_mnu_screen = 0;
}

void update_menu_screen(void)
{
    if (CheckCollisionPointRec(GetMousePosition(), play_button.rect))
    {
        play_button.color = BLUE;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            printf("Click play button\n");
        }
    }
    else
    {
        play_button.color = RED;
    }

    if (CheckCollisionPointRec(GetMousePosition(), exit_button.rect))
    {
        exit_button.color = BLUE;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            exit_game = 1;
        }
    }
    else
    {
        exit_button.color = RED;
    }
    if (CheckCollisionPointRec(GetMousePosition(), about_button.rect))
    {
        about_button.color = BLUE;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            finish_mnu_screen = 1;
        }
    }
    else
    {
        about_button.color = RED;
    }

}

void draw_menu_screen(void)
{
    DrawTexture(menu_texture, 0, 0, RAYWHITE);
    DrawRectangleRounded(play_button.rect, roundness_menu, 0.0f, play_button.color);
    DrawRectangleRoundedLines(play_button.rect, roundness_menu, 0.0f, thickness_menu, PINK);
    DrawRectangleRounded(exit_button.rect, roundness_menu, 0.0f, exit_button.color);
    DrawRectangleRoundedLines(exit_button.rect, roundness_menu, 0.0f, thickness_menu, PINK);
    DrawRectangleRounded(about_button.rect, roundness_menu, 0.0f, about_button.color);
    DrawRectangleRoundedLines(about_button.rect, roundness_menu, 0.0f, thickness_menu, PINK);
    DrawText(play_button.text, play_button.rect.x + play_button.rect.width / 2 - MeasureText(play_button.text, font_size_menu) / 2, play_button.rect.y + play_button.rect.height / 2 - font_size_menu / 2, font_size_menu, BLACK);
    DrawText(exit_button.text, exit_button.rect.x + exit_button.rect.width / 2 - MeasureText(exit_button.text, font_size_menu) / 2, exit_button.rect.y + exit_button.rect.height / 2 - font_size_menu / 2, font_size_menu, BLACK);
    DrawText(about_button.text, about_button.rect.x + about_button.rect.width / 2 - MeasureText(about_button.text, font_size_menu) / 2, about_button.rect.y + about_button.rect.height / 2 - font_size_menu / 2, font_size_menu, BLACK);

}

void unload_menu_screen(void)
{
    UnloadTexture(menu_texture);
    UnloadImage(menu_bg);
}

int finish_menu_screen(void)
{
    return finish_mnu_screen;
}
