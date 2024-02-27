#include "../inc/finish.h"

int startFinish(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Finish");
    SetTargetFPS(60);

    // BACKGROUND
    Texture2D background = LoadTexture("./resource/fin_space.png");

    // PLAYER
    Texture2D playerTexture = LoadTexture("./resource/player.png");
    float playerScaleX = 5.0f;
    float playerScaleY = 5.0f;
    Rectangle player = {160, SCREEN_HEIGHT - playerTexture.height * playerScaleY, 40, 40};

    // CREATE BUTTON
    Button button = CreateCenteredButton("./resource/bttn.png", 0.2f, 0.2f, SCREEN_HEIGHT - 100, (Color){182, 223, 240, 255});

    // FOR JUMPING
    float playerJumpForce = -10.0f;
    float playerGravity = 0.4f;
    bool isJumping = false;
    float startY = player.y;

    // PRESS E
    bool showPressEText = false;
    Texture2D pressETexture = LoadTexture("./resource/hint_E.png");

    // SHOW  WIN TEXT
    bool showYouWinText = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Player moving
        if (IsKeyDown(KEY_RIGHT) && player.x + player.width < SCREEN_WIDTH / 2 - button.rect.width)
        {
            player.x += 2;
        }
        if (IsKeyDown(KEY_LEFT) && player.x > 100)
        {
            player.x -= 2;
        }

        // Jumping
        if (IsKeyDown(KEY_SPACE) && !isJumping)
        {
            isJumping = true;
            startY = player.y;
        }
        if (isJumping)
        {
            playerJumpForce += playerGravity;

            if (player.y + playerJumpForce < 100)
            {
                playerJumpForce = 100 - player.y;
            }

            player.y += playerJumpForce;

            if (player.y >= startY)
            {
                player.y = startY;
                playerJumpForce = -10.0f;
                isJumping = false;
            }
        }

        // Change button color based on collision
        if (IsPlayerCollidingWithButton(player, playerScaleX, playerScaleY, button))
        {
            showPressEText = true;
        }
        else
        {
            showPressEText = false;
        }

        // CHECK PREESS E
        if (showPressEText && IsKeyDown(KEY_E))
        {
            button.color = (Color){215, 189, 91, 155};
            showYouWinText = true;
        }

        DrawTexturePro(background, (Rectangle){0.0f, 0.0f, (float)background.width, (float)-background.height}, (Rectangle){0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT}, (Vector2){0, 0}, 0.0f, WHITE);

        DrawTexturePro(playerTexture, (Rectangle){0, 0, playerTexture.width, playerTexture.height}, (Rectangle){player.x, player.y, playerTexture.width * playerScaleX, playerTexture.height * playerScaleY}, (Vector2){0, 0}, 0.0f, WHITE);

        if (showYouWinText)
        {
            DrawYouWinAnimation();
        }

        DrawButton(button);
        DrawPressEText(button, showPressEText, pressETexture);

        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(playerTexture);
    UnloadTexture(pressETexture);

    CloseWindow();

    return 0;
}

int main(void) {
    startFinish();
    return 0;
}
