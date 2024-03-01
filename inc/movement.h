#ifndef MOVEMENT_H
#define MOVEMENT_H

#define NUM_OF_PLATFORMS 5


#include <raylib.h>

typedef struct {
    float speedX;      //скорость персонажа по горизонтали
    float speedY;      //скорость прыжка
    int screenWidth;   //
    int screenHeight;  //
    float jumpForce;   //сила прыжка
    float gravity;
} SizeData;

extern bool isWalking;
extern int direction;


bool isOnGround(Rectangle *position, const int floorPosition);          //проверка на то, стоит ли персонаж на земле
bool isOnPlatform(Rectangle *position, Rectangle *obstacle);            //проверка на то, стоит ли персонаж на земле
void Jump(Rectangle *position, SizeData *stock, Rectangle platforms[NUM_OF_PLATFORMS]);   //Прыжок
void movement(Rectangle *position, SizeData *stock);             //движение(передвижение по горизонтали) + прыжок
void movement_lvl1(Vector2 *position, SizeData *stock, const int myTextureWidth);
#endif
