#include <raylib.h>
#include <stdio.h>
#include "../inc/screens.h"

Button play_button = {.text = "Play"};
Button exit_button = {.text = "Exit"};
int font_size = 24;
float roundness = 0.5f;
float thickness = 3.0f;
void init_menu_screen(void)
{
    play_button.rect = (Rectangle){GetScreenWidth() / 2 - 50, GetScreenHeight() / 4 - 50, 100, 50};
    play_button.color = RED;
    exit_button.rect = (Rectangle){GetScreenWidth() / 2 - 50, GetScreenHeight() / 4 + 150, 100, 50};
    exit_button.color = RED;
}

void draw_menu_screen(void)
{
    DrawRectangleRounded(play_button.rect, roundness, 0.0f, play_button.color);
    DrawRectangleRoundedLines(play_button.rect, roundness, 0.0f, thickness, PINK);
    DrawRectangleRounded(exit_button.rect, roundness, 0.0f, exit_button.color);
    DrawRectangleRoundedLines(exit_button.rect, roundness, 0.0f, thickness, PINK);
    DrawText(play_button.text, play_button.rect.x + play_button.rect.width / 2 - MeasureText(play_button.text, font_size) / 2, play_button.rect.y + play_button.rect.height / 2 - font_size / 2, font_size, BLACK);
    DrawText(exit_button.text, exit_button.rect.x + exit_button.rect.width / 2 - MeasureText(exit_button.text, font_size) / 2, exit_button.rect.y + exit_button.rect.height / 2 - font_size / 2, font_size, BLACK);
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
            printf("Click exit button\n");
        }
    }
    else
    {
        exit_button.color = RED;
    }
}
