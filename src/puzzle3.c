#include "../inc/puzzle3.h"
#include <stdio.h>

Texture2D background_pz1;

bool clickedThisFrame[NUM_IMAGES] = { false };
int counter = 0;

bool victory_pz3 = false;
double victoryTimer = 0.0;
const double victoryDelay = 1.0;

Rectangle images_pz3[NUM_IMAGES];
bool imagesVisible[NUM_IMAGES];

double timerSeconds = 10.0;

Texture2D imageTextures[NUM_IMAGES];
Texture warning_tex;

Rectangle counterArea = { SCREEN_WIDTH - 564, SCREEN_HEIGHT - 300, 564, 300 };

Rectangle retryButton_pz3 = { (SCREEN_WIDTH - BUTTON_SIZE) / 2 - 10, SCREEN_HEIGHT - BUTTON_SIZE - 240, BUTTON_SIZE + 20, BUTTON_SIZE - 20 };

void init_puzzle3() {
    InitializeImages();
    warning_tex = LoadTexture("resource/warning.png");

    for (int i = 0; i < NUM_IMAGES; i++)
    {
        imageTextures[i] = warning_tex;
    }

    background_pz1 = LoadTexture("resource/computer_screen.png");
}

int do_puzzle3() {

    for (int i = 0; i < NUM_IMAGES; i++)
    {
        if (imagesVisible[i] &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetMousePosition(), images_pz3[i]) &&
            !clickedThisFrame[i])
        {
            imagesVisible[i] = false;
            counter++;
            clickedThisFrame[i] = true;
        }
    }

    if (counter == NUM_IMAGES && !victory_pz3)
    {
        victoryTimer += GetFrameTime();
        if (victoryTimer >= victoryDelay)
        {
            victory_pz3 = true;
        }
    }

    if (!victory_pz3)
    {
        timerSeconds -= GetFrameTime();
        if (timerSeconds <= 0)
        {

            for (int i = 0; i < NUM_IMAGES; i++)
            {
                imagesVisible[i] = false;
            }
        }
    }


    //DrawTexture(background_pz1, SCREEN_WIDTH / 2 - background_pz1.width / 2, SCREEN_HEIGHT / 2 - background_pz1.height / 2, WHITE);
    DrawTextureEx(background_pz1, (Vector2) { (SCREEN_WIDTH / 2) - (background_pz1.width * 9 / 2), (SCREEN_HEIGHT / 2) - (background_pz1.height * 9 / 2) }, 0 ,9.0, WHITE );

    for (int i = 0; i < NUM_IMAGES; i++)
    {
        if (imagesVisible[i])
        {
            DrawTextureRec(imageTextures[i], (Rectangle) { 0, 0, imageTextures[i].width, imageTextures[i].height }, (Vector2) { images_pz3[i].x, images_pz3[i].y }, WHITE);
        }
    }

    DrawText(TextFormat("%d/%d", counter, NUM_IMAGES), counterArea.x = 830, counterArea.y = 470, 30, WHITE);

    if (victory_pz3)
    {
        DrawText("Problem solved!", SCREEN_WIDTH / 2 - MeasureText("Problem solved!", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, GREEN);
    }
    else if (timerSeconds <= 0)
    {
        DrawText("Time is up.", SCREEN_WIDTH / 2 - MeasureText("Time is up.", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, RED);


        DrawRectangleRec(retryButton_pz3, Fade(DARKPURPLE, 0.3));
        DrawRectangleLinesEx(retryButton_pz3, 2, DARKPURPLE);
        DrawText("Retry", retryButton_pz3.x + BUTTON_SIZE / 2 + 10 - MeasureText("Retry", 20) / 2, retryButton_pz3.y + BUTTON_SIZE / 2 - 20, 20, WHITE);


        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetMousePosition(), retryButton_pz3))
        {

            InitializeImages();
            counter = 0;
            victory_pz3 = false;
            timerSeconds = 15.0;
        }
    }
    else
    {
        int displaySeconds = (int)timerSeconds;
        DrawText(TextFormat("Time: 00:%02d", displaySeconds), 370, 220, 25, WHITE);
    }



    for (int i = 0; i < NUM_IMAGES; i++)
    {
        clickedThisFrame[i] = false;
    }

    if (victory_pz3) {
        return 1;
    }
    return 0;
}

void InitializeImages(void)
{
    Vector2 imagePositions[NUM_IMAGES] = {
        {500, 240},
        {380, 350},
        {600, 360},
        {700, 230},
        {400, 260},
        {800, 320},
        {530, 430},
        {830, 220},
        {490, 360},
        {420, 410},
        {680, 315},
        {620, 255},
        {680, 415},
        {755, 390},
        {540, 310},
    };

    for (int i = 0; i < NUM_IMAGES; i++)
    {
        images_pz3[i].x = imagePositions[i].x;
        images_pz3[i].y = imagePositions[i].y;
        images_pz3[i].width = IMAGE_WIDTH;
        images_pz3[i].height = IMAGE_HEIGHT;
        imagesVisible[i] = true;
    }
}

bool CheckOverlap(int index)
{
    for (int i = 0; i < index; i++)
    {
        if (CheckCollisionRecs(images_pz3[i], images_pz3[index]))
        {
            return true;
        }
    }
    return false;
}
