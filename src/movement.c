
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
    if (position->y == (obstacle->y - position->height) && (position->x <= (obstacle->x * obstacle->width)
                                                            || position->x >= (obstacle->x * obstacle->width ) + 1)) {
        return true;
    } else {
        return false;
    }
}

void Jump(Rectangle *position, SizeData *stock, Rectangle *obstacle) {
    const int floorPos = 600;
    int charOnPlatformPos = obstacle->y - position->height;

    if (IsKeyPressed(KEY_SPACE) && (isOnPlatform(position, obstacle)
                                    || isOnGround(position, floorPos))) {


        stock->speedY = -stock->jumpForce;
    }

    position->y += stock->speedY;
    stock->speedY += stock->gravity;

    if (CheckCollisionRecs(*position, *obstacle)) {
        if (stock->speedY > 0) {
            stock->speedY = 0;
            position->y = charOnPlatformPos;
        } else if (stock->speedY < 0) {
            // Если персонаж двигается вверх и сталкивается с платформой снизу, он начинает падать
            stock->speedY = 0;
            position->y = obstacle->y + obstacle->height;
        }
    }
    if (isOnGround(position, floorPos)) {
        stock->speedY = 0;
        position->y = floorPos;
    }
    if (isOnPlatform(position, obstacle)) {

        stock->speedY = 0;
        position->y = charOnPlatformPos;
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
