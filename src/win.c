#include "../inc/finish.h"

void DrawYouWinAnimation(void)
{
    static int fontSize = 50;
    static Color color = {0, 20, 37, 0};

    if (color.a < 255)
    {
        color.a += 5;
        fontSize += 2;
    }

    float spacing = 2.0f;

    DrawTextEx(GetFontDefault(), "YOU WIN !", (Vector2){GetScreenWidth() / 2 - MeasureText("YOU WIN", fontSize) / 2, GetScreenHeight() / 2 - fontSize / 2}, fontSize, spacing, color);
}



