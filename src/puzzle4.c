#include "../inc/puzzle4.h"

ImageInfo images[MAX_IMAGES];
Texture2D background_texture;
Texture2D checkmarkTexture;

Vector2 targetPoints[NUM_TARGET_POINTS];
bool targetReached[NUM_TARGET_POINTS] = { false };

#define MIN_X 320
#define MIN_Y 150
#define MAX_X 320 + 640
#define MAX_Y 150 + 360

double startTime = 0.0;

void init_puzzle4() {
    background_texture = LoadTexture("resource/space2.png");
    checkmarkTexture = LoadTexture("resource/checkmark.png");

    targetPoints[0] = (Vector2){ 520 , 370 };
    targetPoints[1] = (Vector2){ 850 , 230 };
    targetPoints[2] = (Vector2){ 680 , 300 };
    targetPoints[3] = (Vector2){ 420 , 420 };

    images[0].position = (Vector2){ 770, 400 };
    images[0].texture = LoadTexture("resource/yellowplanet.png");
    images[0].isDragging = false;
    images[0].scale = 0.8;
    images[0].right_target_index = 2;

    images[1].position = (Vector2){ 600, 200 };
    images[1].texture = LoadTexture("resource/blueplanet.png");
    images[1].isDragging = false;
    images[1].scale = 0.9;
    images[1].right_target_index = 0;

    images[2].position = (Vector2){ 400, 250 };
    images[2].texture = LoadTexture("resource/purpleplanet.png");
    images[2].isDragging = false;
    images[2].scale = 0.7;
    images[2].right_target_index = 3;

    images[3].position = (Vector2){ 550, 370 };
    images[3].texture = LoadTexture("resource/redplanet.png");
    images[3].isDragging = false;
    images[3].scale = 1.2;
    images[3].right_target_index = 1;
}


void update_puzzle4() {
    for (int i = 0; i < MAX_IMAGES; i++) {
        Rectangle imageRec = { images[i].position.x, images[i].position.y, images[i].texture.width * images[i].scale, images[i].texture.height * images[i].scale };

        if (CheckCollisionPointRec(GetMousePosition(), imageRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                images[i].isDragging = true;
        }

        if (images[i].isDragging) {

            images[i].position.x = GetMouseX() - images[i].texture.width * images[i].scale / 2;
            images[i].position.y = GetMouseY() - images[i].texture.height * images[i].scale / 2;
            
        }

        if (!images[i].isDragging) {
            for (int j = 0; j < NUM_TARGET_POINTS; j++) {
                if (!targetReached[j] && CheckCollisionPointRec(targetPoints[j], imageRec) && images[i].right_target_index == j) {
                    targetReached[j] = true;
                    startTime = GetTime();
                    break;
                }
            }
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        for (int i = 0; i < MAX_IMAGES; i++) {
            images[i].isDragging = false;
        }
    }
}

void draw_puzzle4() {
    DrawTextureEx(background_texture, (Vector2) { 320, 150 }, 0.0, 1.0, WHITE);

    for (int j = 0; j < NUM_TARGET_POINTS; j++) {
        DrawCircleV(targetPoints[j], 10, WHITE);

        if (targetReached[j]) {
            DrawTextureEx(checkmarkTexture, (Vector2) { targetPoints[j].x - 10, targetPoints[j].y - 50 }, 0.0, 1.0, GREEN);
        }
    }

    for (int i = 0; i < MAX_IMAGES; i++) {
        DrawTextureEx(images[i].texture, images[i].position, 0, images[i].scale, RAYWHITE);
    }
}

int do_puzzle4() {
    update_puzzle4();
    draw_puzzle4();
    if (targetReached[0] && targetReached[1] && targetReached[2] && targetReached[3]) {
        return 1;
    }
    return 0;
}
