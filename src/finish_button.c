#include "../inc/finish.h"

Button CreateButton(const char *texturePath, float scaleX, float scaleY, int x, int y, Color color)
{
    Button button;
    button.texture = LoadTexture(texturePath);
    button.rect = (Rectangle){x, y, button.texture.width * scaleX, button.texture.height * scaleY};
    button.color = color;
    return button;
}

void DrawButton(Button button)
{
    DrawTexturePro(button.texture, (Rectangle){0, 0, button.texture.width, button.texture.height}, button.rect, (Vector2){0, 0}, 0.0f, button.color);
}

Button CreateCenteredButton(const char *texturePath, float scaleX, float scaleY, int y, Color color)
{
    Button button;
    button.texture = LoadTexture(texturePath);
    button.rect = (Rectangle){(GetScreenWidth() - button.texture.width * scaleX) / 2, y, button.texture.width * scaleX, button.texture.height * scaleY};
    button.color = color;
    return button;
}

bool IsPlayerCollidingWithButton(Rectangle player, float playerScaleX, float playerScaleY, Button button)
{
    Rectangle playerRect = {player.x, player.y, player.width * playerScaleX, player.height * playerScaleY};
    return CheckCollisionRecs(playerRect, button.rect);
}

void DrawPressEText(Button button, bool showText, Texture2D pressETexture)
{
    if (showText)
    {
        // Располагаем увеличенную текстуру по центру кнопки
        float textureX = button.rect.x + button.rect.width / 2 - (pressETexture.width * 2) / 2; 
        // Учитываем новый размер текстуры
        float textureY = button.rect.y - pressETexture.height * 2 - 10; // 10 - расстояние между увеличенной текстурой и кнопкой
        DrawTexturePro(pressETexture, (Rectangle){0, 0, pressETexture.width, pressETexture.height}, (Rectangle){textureX, textureY, pressETexture.width * 2, pressETexture.height * 2}, (Vector2){0, 0}, 0.0f, WHITE);
    }
}
