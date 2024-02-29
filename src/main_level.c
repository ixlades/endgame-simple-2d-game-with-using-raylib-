#include "../inc/main_level.h"

Texture2D main_bg;
Texture2D platformTexture;
Texture2D characterTexture;

Rectangle platform[NUM_OF_PLATFORMS];
Rectangle characer;

SizeData stock;

void init_main_level(void) {
    main_bg = LoadTexture("resource/finish_bg.png");
    platformTexture = LoadTexture("resource/platform.png");
    characterTexture = LoadTexture("resource/player.png");

    //---------------------------Stock------------------------------------
    stock.screenHeight = GetScreenHeight();
    stock.screenWidth = GetScreenWidth();
    stock.speedX = 10.0f;
    stock.speedY = 1.0f;
    stock.jumpForce = 15;
    stock.gravity = 0.5f;

    //---------------------------Character------------------------------------
    characer = (Rectangle){ 100, 500 , characterTexture.width, characterTexture.height};

    //---------------------------Platforms------------------------------------
    platform[0] = (Rectangle){ 0, 200, platformTexture.width, platformTexture.height };
    platform[1] = (Rectangle){ platformTexture.width - 100 , 300 + platformTexture.height,
                               platformTexture.width, platformTexture.height };
    platform[2] = (Rectangle){ 150 + platformTexture.width, 400 + platformTexture.height,
                               platformTexture.width, platformTexture.height };
    platform[3] = (Rectangle){ 400 + platformTexture.width, 500 + platformTexture.height,
                               platformTexture.width, platformTexture.height };
}

void draw_platforms(void) {
    // DrawTexture(platformTexture, platform1.x, platform1.y, WHITE);
    for (int i = 0; i < NUM_OF_PLATFORMS; ++i) {
        DrawTexture(platformTexture, platform[i].x, platform[i].y, WHITE);
    }
}
void draw_main_level(void) {
    // DrawTexture(main_bg, 0, 0, WHITE);
    DrawTexturePro(
        main_bg,
        (Rectangle){0.0f, 0.0f, (float)main_bg.width,
                    (float)-main_bg.height},
        (Rectangle){0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT},
        (Vector2){0, 0}, 0.0f, WHITE);
    draw_platforms();
    DrawTexture(characterTexture, characer.x, characer.y, WHITE);
}

void update_main_level(void) {
    movement(&characer, &stock);
    Jump(&characer, &stock, platform);
}
void unload_main_level(void) {
    UnloadTexture(main_bg);
    UnloadTexture(characterTexture);
    UnloadTexture(platformTexture);
}
