#include "../inc/main_level.h"

void init_main_level(void) {
    main_bg = LoadTexture("resource/space-back");
    platformTexture = LoadTexture("resource/platform");
    characterTexture = LoadTexture("resource/skeleton");

    //---------------------------Stock------------------------------------
    stock.screenHeight = SCREEN_HEIGHT;
    stock.screenWidth = SCREEN_WIDTH;
    stock.speedX = 2;
    stock.speedY = 0.0f;
    stock.jumpForce = 7;
    stock.gravity = 0.1f;

    //---------------------------Character------------------------------------
    characer = (Rectangle){ 0, 600 , characterTexture.width, characterTexture.height };

    //---------------------------Platforms------------------------------------
    platforms[0] = (Rectangle){ 0, 200, platformTexture.width, platformTexture.height };
    platforms[1] = (Rectangle){ 50 + platformTexture.width, 300 + platformTexture.height,
                                platformTexture.width, platformTexture.height };
    platforms[2] = (Rectangle){ 100 + platformTexture.width, 400 + platformTexture.height,
                                platformTexture.width, platformTexture.height };
    platforms[3] = (Rectangle){ 150 + platformTexture.width, 500 + platformTexture.height,
                                platformTexture.width, platformTexture.height };
}
