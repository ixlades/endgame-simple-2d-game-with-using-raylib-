#ifndef HEADER_H
#define HEADER_H

#include <raylib.h>

typedef struct {
    float speedX;      //скорость персонажа по горизонтали
    float speedY;      //скорость прыжка
    int screenWidth;   //
    int screenHeight;  //
    float jumpForce;   //сила прыжка
    float gravity;     //

} SizeData;

bool isOnGround(Vector2 *position, const int floorPosition);    //проверка на то, стоит ли персонаж на земле
void movement(Vector2 *position, SizeData *stock, const int myTextureWidth); //движение(передвижение по горизонтали и прыжок)

#endif
