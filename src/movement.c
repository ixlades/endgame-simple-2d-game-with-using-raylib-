#include "header.h"

bool isOnGround(Vector2 *position, const int floorPosition) {
    if (position->y >= floorPosition) {
        return true;
    } else {
        return false;
    }
}

void movement(Vector2 *position, SizeData *stock, const int myTextureWidth) {
    const int floorPosition = stock->screenHeight / 2;

    //    --------Движение по x----------
    if ((position->x + stock->speedX) <= stock->screenWidth - myTextureWidth) {
        if (IsKeyDown(KEY_RIGHT)) position->x += stock->speedX;
    }
    if ((position->x - stock->speedX) >= 0) {
        if (IsKeyDown(KEY_LEFT)) position->x -= stock->speedX;
    }

    //       --------Прыжок----------
    if (IsKeyPressed(KEY_SPACE) && isOnGround(position, floorPosition)) {
        stock->speedY = -stock->jumpForce;
    }

    // Логика прыжка
    position->y += stock->speedY;
    stock->speedY += stock->gravity;

    if(isOnGround(position, floorPosition)) {
        stock->speedY = 0;
        position->y = floorPosition;
    }
}






