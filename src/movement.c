#include "../inc/movement.h"

bool isOnGround(Rectangle *position, int floorPosition) {
    if (position->y >= floorPosition) {
        return true;
    }
    else
    {
        return false;
    }
}

bool isOnPlatform(Rectangle *position, Rectangle *obstacle) {
    return CheckCollisionRecs(*position, *obstacle);
}

void Jump(Rectangle *position, SizeData *stock, Rectangle platforms[NUM_OF_PLATFORMS]) {
    const int floorPos = 600;
    int i;

    for (i = 0; i < NUM_OF_PLATFORMS; i++) {
        Rectangle *obstacle = &platforms[i];
        int charOnPlatformPos = obstacle->y - position->height;

        // Проверяем столкновение с платформой или землей
        if (IsKeyPressed(KEY_SPACE) && (isOnPlatform(position, obstacle) || isOnGround(position, floorPos))) {
            stock->speedY = -stock->jumpForce;
        }

        position->y += stock->speedY;
        stock->speedY += stock->gravity;

        if (CheckCollisionRecs(*position, *obstacle)) {
            if (stock->speedY > 0) {
                // При столкновении с платформой снизу
                stock->speedY = 0;
                position->y = charOnPlatformPos;
            } else if (stock->speedY < 0) {
                stock->speedY = 0;
                position->y = obstacle->y + obstacle->height;
            }
        }
    }

    if (isOnGround(position, floorPos)) {
        stock->speedY = 0;
        position->y = floorPos;
    }
}

void movement(Rectangle *position, SizeData *stock) {
    if ((position->x + stock->speedX) <= stock->screenWidth - position->width) {
        if (IsKeyDown(KEY_RIGHT)) position->x += stock->speedX;
    }
    if ((position->x - stock->speedX) >= 0) {
        if (IsKeyDown(KEY_LEFT)) position->x -= stock->speedX;
    }
}
