#ifndef MOVEMENT_H
#define MOVEMENT_H


#include <raylib.h>

typedef struct {
    float speedX;      //скорость персонажа по горизонтали
    float speedY;      //скорость прыжка
    int screenWidth;   //
    int screenHeight;  //
    float jumpForce;   //сила прыжка
    float gravity;
} SizeData;



bool isOnGround(Rectangle *position, const int floorPosition);          //проверка на то, стоит ли персонаж на земле
bool isonPlatform(Rectangle *position, Rectangle *obstacle);            //проверка на то, стоит ли персонаж на земле
void Jump(Rectangle *position, SizeData *stock, Rectangle *obstacle);   //Прыжок + проверка на колизию(платформы)
void movement(Rectangle *position, SizeData *stock);                    //движение(передвижение по горизонтали)


#endif
