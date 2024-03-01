#include "raylib.h"
#include "../inc/player.h"
#include "../inc/movement.h"
#include "../inc/screens.h"
#include "../inc/timer.h"

Texture2D background;
Texture2D playerTexture;
float playerScaleX;
float playerScaleY;
bool showPressEText;
bool showYouWinText;
Image char_stand_img_finish;
Texture2D char_stand_right_finish;
Texture2D char_stand_left_finish;
Image char_walk1_img_finish;
Texture2D char_walk1_right_finish;
Texture2D char_walk1_left_finish;
Image char_walk2_img_finish;
Texture2D char_walk2_right_finish;
Texture2D char_walk2_left_finish;
Texture2D pressETexture;
SizeData stock_finish;
ButtonFinish centered_button;

static int finish_last_level;
int animation_time;


void DrawYouWinAnimation(void) {
    static int fontSize = 50;
    static Color color = {0, 20, 37, 0};

    if (color.a < 255) {
        color.a += 5;
        fontSize += 2;
    }

    float spacing = 2.0f;

    DrawTextEx(
        GetFontDefault(), "YOU WIN !",
        (Vector2){GetScreenWidth() / 2 - MeasureText("YOU WIN", fontSize) / 2,
                  GetScreenHeight() / 2 - fontSize / 2},
        fontSize, spacing, color);
}

void DrawYouLoseAnimation(void) {
    static int fontSize = 50;
    static Color color = {234, 186, 74, 0};

    if (color.a < 255) {
        color.a += 5;
        fontSize += 2;
    }

    float spacing = 2.0f;

    DrawTextEx(
        GetFontDefault(), "YOU LOSE . .",
        (Vector2){GetScreenWidth() / 2 - MeasureText("YOU LOSE", fontSize) / 2,
                  GetScreenHeight() / 2 - fontSize / 2},
        fontSize, spacing, color);
}

void DrawButton(ButtonFinish button) {
    DrawTexturePro(
        button.texture,
        (Rectangle){0, 0, button.texture.width, button.texture.height},
        button.rect, (Vector2){0, 0}, 0.0f, button.color);
}

void CreateCenteredButton(const char *texturePath, float scaleX, float scaleY,
                          int y, Color color) {
    centered_button.texture = LoadTexture(texturePath);
    centered_button.rect = (Rectangle){
        (GetScreenWidth() - centered_button.texture.width * scaleX) / 2, y,
        centered_button.texture.width * scaleX,
        centered_button.texture.height * scaleY};
    centered_button.color = color;

}


bool IsPlayerCollidingWithButton(Player *player_instance, float playerScaleX,
                                 float playerScaleY, ButtonFinish button) {
    Rectangle playerRect = {player_instance->pos.x, player_instance->pos.y, player_instance->texture.width * playerScaleX,
                            player.texture.height * playerScaleY};
    return CheckCollisionRecs(playerRect, button.rect);
}

void DrawPressEText(ButtonFinish button, bool showText, Texture2D pressETexture) {
    if (showText) {
        // Располагаем увеличенную текстуру по центру кнопки
        float textureX = button.rect.x + button.rect.width / 2 -
                         (pressETexture.width * 2) / 2;
        // Учитываем новый размер текстуры
        float textureY =
            button.rect.y - pressETexture.height * 2 -
            10;  // 10 - расстояние между увеличенной текстурой и кнопкой
        DrawTexturePro(
            pressETexture,
            (Rectangle){0, 0, pressETexture.width, pressETexture.height},
            (Rectangle){textureX, textureY, pressETexture.width * 2.5,
                        pressETexture.height * 2.5},
            (Vector2){0, 0}, 0.0f, WHITE);
    }
}

void init_finish_screen(void) {
    finish_last_level = 0;
    animation_time = 300;
    showYouWinText = false;
    showPressEText = false;
    playerScaleX = 5.0f;
    playerScaleY = 5.0f;
    background = LoadTexture("resource/finish_bg.png");
    
    char_stand_img_finish = LoadImage("resource/player.png");
    char_stand_right_finish = LoadTextureFromImage(char_stand_img_finish);
    ImageFlipHorizontal(&char_stand_img_finish);
    char_stand_left_finish = LoadTextureFromImage(char_stand_img_finish);
    char_walk1_img_finish = LoadImage("resource/walk1.png");
    char_walk1_right_finish = LoadTextureFromImage(char_walk1_img_finish);
    ImageFlipHorizontal(&char_walk1_img_finish);
    char_walk1_left_finish = LoadTextureFromImage(char_walk1_img_finish);
    char_walk2_img_finish = LoadImage("resource/walk2.png");
    char_walk2_right_finish = LoadTextureFromImage(char_walk2_img_finish);
    ImageFlipHorizontal(&char_walk2_img_finish);
    char_walk2_left_finish = LoadTextureFromImage(char_walk2_img_finish);
    stock_finish.speedX = 10.0f;
    stock_finish.speedY = 1.0f;
    stock_finish.screenWidth = GetScreenWidth();
    stock_finish.screenHeight = GetScreenHeight();
    stock_finish.jumpForce = 15;
    stock_finish.gravity = 0.5f;
    player.texture = LoadTexture("resource/player.png");
    player.pos = (Vector2){160,500};
    player.isWalking = false;
    player.direction = 0;
    
    CreateCenteredButton("resource/finish_btn.png", 0.2f, 0.2f,
                         SCREEN_HEIGHT - 150, (Color){182, 223, 240, 255});

    pressETexture = LoadTexture("resource/hint_E.png");
}

void update_finish_screen(void) {
    // StartTimer();
    movement_lvl1(&player.pos, &stock_finish, player.texture.width);
    if (player.isWalking) {
        double time = GetTime() * 10;
        if (player.direction == -1) {
            if (((int)time) % 2 == 0) {
                player.texture = char_walk1_left_finish;
            } else {
                player.texture = char_walk2_left_finish;
            }
        } else {
            if (((int)time) % 2 == 0) {
                player.texture = char_walk1_right_finish;
                
            } else {
                player.texture = char_walk2_right_finish;
            }
        }
        player.isWalking = false;
    } else {
        if (player.direction == -1) {
            player.texture = char_stand_left_finish;
        } else {
            player.texture = char_stand_right_finish;
        }

    }
    // CHANGE BUTTON COLOR BASED ON COLLISION
    if (IsPlayerCollidingWithButton(&player, playerScaleX, playerScaleY,
                                    centered_button)) {
        showPressEText = true;
    } else {
        showPressEText = false;
    }

    // CHECK PREESS E
    if (showPressEText && IsKeyDown(KEY_E)) {
        centered_button.color = (Color){215, 189, 91, 155};
        showYouWinText = true;
        // StopTimer();
        
    }
    
}

void draw_finish_screen(void) {
    DrawTexturePro(
        background,
        (Rectangle){0.0f, 0.0f, (float)background.width,
                    (float)-background.height},
        (Rectangle){0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT},
        (Vector2){0, 0}, 0.0f, WHITE);

    DrawTexturePro(
        player.texture,
        (Rectangle){0, 0, player.texture.width, player.texture.height},
        (Rectangle){player.pos.x, player.pos.y, player.texture.width * playerScaleX,
                    player.texture.height * playerScaleY},
        (Vector2){0, 0}, 0.0f, WHITE);
    DrawButton(centered_button);
    DrawPressEText(centered_button, showPressEText, pressETexture);
    // TimerText();
    // if (timer == 0) {
    //     showYouWinText = false;
    //     DrawYouLoseAnimation();
    //     animation_time--;
    // }

    // // CHECK WIN
    if (showYouWinText) {
        DrawYouWinAnimation();
        animation_time--;
    }
    if (animation_time <= 0) {
        finish_last_level = 1;
    }
}

void unload_finish_screen(void) {
    UnloadTexture(centered_button.texture);
    UnloadTexture(background);
    UnloadTexture(pressETexture);
    UnloadTexture(player.texture);
}

int finish_last_screen(void) {
    return finish_last_level;
}
