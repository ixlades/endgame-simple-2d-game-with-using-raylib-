#ifndef FINISH_H
#define FINISH_H

#include "raylib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct Button
{
    Rectangle rect;
    Texture2D texture;
    Color color;
} Button;

// LOAD TEXTURE
// void loadBackgroundTexture(void);

Button CreateButton(const char *texturePath, float scaleX, float scaleY, int x, int y, Color color);
void DrawButton(Button button);
Button CreateCenteredButton(const char *texturePath, float scaleX, float scaleY, int y, Color color);
bool IsPlayerCollidingWithButton(Rectangle player, float playerScaleX, float playerScaleY, Button button);
void DrawPressEText(Button button, bool showText, Texture2D pressETexture);

// WIN TEXT
void DrawYouWinAnimation(void);

#endif