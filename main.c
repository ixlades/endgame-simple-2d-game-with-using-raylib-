#include "list.h"

//test comm

int main(void) {
    // Инициализация Raylib и создание окна
    InitWindow(1280, 700, "Raylib Test");
    Vector2 position = { 100.0f, 100.0f };
    Vector2 texturePosition = { 0.0f, 0.0f };
    
    Texture2D fenceTexture = LoadTexture("stop.png");
    Rectangle sourceRecOfFence = { 0.0f, 0.0f, (float)fenceTexture.width, (float)fenceTexture.height };

    Texture2D myTexture = LoadTexture("skeleton.png");
    Rectangle sourceRec = { 0.0f, 0.0f, (float)myTexture.width, (float)myTexture.height };

    // Размеры, на которые мы уменьшим текстуру (в данном случае, уменьшение в два раза)
    Rectangle destRec = { 0.0f, 0.0f, (float)myTexture.width, (float)myTexture.height };
    // Скорость движения
    float speed = 0.5f;

    Color highlightColor = {255, 0, 255, 100}; // Полупрозрачный голубой
    float highlightRadius = 30.0f;

    bool highlightActive = false;
    // Основной цикл
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_TAB)) {
            // Переключение состояния подсветки при каждом нажатии Tab
            highlightActive = !highlightActive;
        }

        if ((position.x + speed) <= 920) {
            if (IsKeyDown(KEY_RIGHT)) position.x += speed;
        }
        if ((position.x - speed) >= 0) {
            if (IsKeyDown(KEY_LEFT)) position.x -= speed;
        }
        if ((position.y + speed) <= 400) {
            if (IsKeyDown(KEY_DOWN)) position.y += speed;
        }
        if ((position.y - speed) >= 0) {
            if (IsKeyDown(KEY_UP)) position.y -= speed;
        }
        BeginDrawing();
        ClearBackground((Color){0, 255, 255, 255});

        // Ваш код отрисовки и логики здесь
        DrawTexturePro(myTexture, destRec,  (Rectangle){ position.x, position.y, destRec.width, destRec.height },
                       (Vector2){0, 0}, 0, WHITE);

        if (highlightActive) {
            Vector2 mousePosition = GetMousePosition();
            DrawCircleV(mousePosition, highlightRadius, highlightColor);
        }
        EndDrawing();
    }

    // Закрытие окна Raylib
    CloseWindow();
    UnloadTexture(myTexture);
    return 0;
}




