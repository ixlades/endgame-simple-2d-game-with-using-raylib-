#include <raylib.h>
#include "../inc/constants.h"
#include "../inc/screens.h"

enum GameScreen current_screen = MENU;

int main(void)
{
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Title");
    init_menu_screen();
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        switch (current_screen)
        {
        case MENU:
            draw_menu_screen();
            break;
        default:
            break;
        }

        EndDrawing();
    }
    CloseWindow();
}
