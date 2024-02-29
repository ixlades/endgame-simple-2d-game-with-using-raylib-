#include "../inc/puzzle1.h"

bool gameOver = false;
bool victory = false;
bool wrongCodeEntered = false;

Texture2D background_texture;

int enteredCode[CODE_LENGTH] = { 0 };
int codeIndex = 0;

Rectangle buttons[10];
Color buttonColors[10];

//int sequence[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };  // ПАРОЛЬ 
int sequence[] = { 9, 1, 6, 7, 8, 10, 3, 2, 4, 5};

Rectangle retryButton = { (SCREEN_WIDTH - BUTTON_SIZE) / 2 - 10, SCREEN_HEIGHT - BUTTON_SIZE - 240, BUTTON_SIZE + 20, BUTTON_SIZE - 20 };

void init_puzzle1() {
    background_texture = LoadTexture("C:/Users/38097/Desktop/repos/resource/backgroundcode.png");

    int numRows = 2;
    int numColumns = BUTTONS_PER_ROW;

    float totalButtonWidth = numColumns * BUTTON_SIZE + (numColumns - 1) * BUTTON_MARGIN;
    float startX = (SCREEN_WIDTH - totalButtonWidth) / 2;

    for (int i = 0; i < 10; i++)
    {
        int row = i / numColumns;
        int col = i % numColumns;

        buttons[i].x = startX + col * (BUTTON_SIZE + BUTTON_MARGIN);
        buttons[i].y = SCREEN_HEIGHT / 2 - numRows * (BUTTON_SIZE + BUTTON_MARGIN) / 2 + row * (BUTTON_SIZE + BUTTON_MARGIN) - 20;
        buttons[i].width = BUTTON_SIZE;
        buttons[i].height = BUTTON_SIZE;

        buttonColors[i] = DARKBLUE;
    }


}

int do_puzzle1() {
    //int result = 0;

    if (!gameOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePosition = GetMousePosition();

        for (int i = 0; i < 10; i++)
        {
            if (CheckCollisionPointRec(mousePosition, buttons[i]))
            {
                enteredCode[codeIndex] = i + 1;
                codeIndex++;

                if (codeIndex >= CODE_LENGTH)
                {
                    bool correctCode = true;

                    for (int j = 0; j < CODE_LENGTH; j++)
                    {
                        if (enteredCode[j] != sequence[j])
                        {
                            correctCode = false;
                            break;
                        }
                    }

                    if (correctCode)
                    {
                        victory = true;
                    }
                    else
                    {
                        wrongCodeEntered = true;
                    }

                    gameOver = true;
                }

                // изменение цвета кнопки при нажатии УРАААААААА
                buttonColors[i] = PURPLE;

                break;
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePosition = GetMousePosition();

        // клик retry 
        if (CheckCollisionPointRec(mousePosition, retryButton) && wrongCodeEntered)
        {
            gameOver = false;
            victory = false;
            wrongCodeEntered = false;
            codeIndex = 0;


            for (int i = 0; i < 10; i++)
            {
                buttonColors[i] = DARKBLUE;
            }
        }
    }

    Vector2 background_pos = { .x = 320, .y = 150 };
    DrawTextureEx(background_texture, background_pos, 0.0, 1.0, WHITE);

    ClearBackground(RAYWHITE);

    for (int i = 0; i < 10; i++)
    {
        // кнопка с обводом
        DrawRectangleRec(buttons[i], Fade(buttonColors[i], 0.3));
        DrawRectangleLinesEx(buttons[i], 2, DARKBLUE);
        DrawText(TextFormat("%d", i + 1), buttons[i].x + BUTTON_SIZE / 2 - MeasureText(TextFormat("%d", i + 1), 20) / 2, buttons[i].y + BUTTON_SIZE / 2 - 10, 20, WHITE);
    }

    if (gameOver)
    {
        if (wrongCodeEntered)
        {
            DrawRectangleRec(retryButton, Fade(DARKPURPLE, 0.3));
            DrawRectangleLinesEx(retryButton, 2, DARKPURPLE);
            DrawText("Retry", retryButton.x + BUTTON_SIZE / 2 + 10 - MeasureText("Retry", 20) / 2, retryButton.y + BUTTON_SIZE / 2 - 20, 20, WHITE);
        }

        if (victory)
        {
            DrawText("You entered the correct code!", 450, SCREEN_HEIGHT - 500, 25, GREEN);
            return 1;
        }
        else
        {
            DrawText("Wrong code entered.", 510, SCREEN_HEIGHT / 3.2, 25, RED);
        }
    }

    return 0;
}
