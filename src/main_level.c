#include "../inc/main_level.h"
#include "../inc/player.h"


int direction = 0;
bool isWalking = false;

Texture2D main_bg;
Texture2D platformTexture;
Texture2D characterTexture;
Texture2D doorMainLevelTexture;

Rectangle platform[NUM_OF_PLATFORMS];
Rectangle characer;
Rectangle doorMainLevel;

Image char_stand_img_level2;
Texture2D char_stand_right_level2;
Texture2D char_stand_left_level2;
Image char_walk1_img_level2;
Texture2D char_walk1_right_level2;
Texture2D char_walk1_left_level2;
Image char_walk2_img_level2;
Texture2D char_walk2_right_level2;
Texture2D char_walk2_left_level2;

SizeData stock;

void init_main_level(void) {
    main_bg = LoadTexture("resource/finish_bg.png");
    platformTexture = LoadTexture("resource/platform1.png");
    characterTexture = LoadTexture("resource/player.png");
    doorMainLevelTexture = LoadTexture("resource/door_lvl_one.png");

    char_stand_img_level2 = LoadImage("resource/player.png");
    char_stand_right_level2 = LoadTextureFromImage(char_stand_img_level2);
    ImageFlipHorizontal(&char_stand_img_level2);
    char_stand_left_level2 = LoadTextureFromImage(char_stand_img_level2);

    char_walk1_img_level2 = LoadImage("resource/walk1.png");
    char_walk1_right_level2 = LoadTextureFromImage(char_walk1_img_level2);
    ImageFlipHorizontal(&char_walk1_img_level2);
    char_walk1_left_level2 = LoadTextureFromImage(char_walk1_img_level2);

    char_walk2_img_level2 = LoadImage("resource/walk2.png");
    char_walk2_right_level2 = LoadTextureFromImage(char_walk2_img_level2);
    ImageFlipHorizontal(&char_walk2_img_level2);
    char_walk2_left_level2 = LoadTextureFromImage(char_walk2_img_level2);

    //---------------------------Stock------------------------------------
    stock.screenHeight = GetScreenHeight();
    stock.screenWidth = GetScreenWidth();
    stock.speedX = 10.0f;
    stock.speedY = 1.0f;
    stock.jumpForce = 15;
    stock.gravity = 0.5f;

    //---------------------------Character------------------------------------
    characer = (Rectangle){ 100, 600 , characterTexture.width * 2 , (characterTexture.height * 3)};

    //---------------------------Platforms------------------------------------
    platform[0] = (Rectangle){ 0, 200, platformTexture.width, platformTexture.height };
    platform[1] = (Rectangle){ 1280 - platformTexture.width, 300 + platformTexture.height,
                               platformTexture.width, platformTexture.height };
    platform[2] = (Rectangle){ 150 + platformTexture.width, 400 + platformTexture.height,
                               platformTexture.width, platformTexture.height };
    platform[3] = (Rectangle){ 400 + platformTexture.width, 500 + platformTexture.height,
                               platformTexture.width, platformTexture.height };
    //------------------------------Door-----------------------------------
    doorMainLevel = (Rectangle){ 1280 - doorMainLevelTexture.width * 4, 300 + platformTexture.height - doorMainLevelTexture.height * 5,
                                 doorMainLevelTexture.width * 4 , doorMainLevelTexture.height * 5 };
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
    DrawTextureEx(characterTexture, (Vector2){characer.x - characer.width, characer.y - characer.height + 25}, 0.0, 6.0, WHITE);
    DrawTextureEx(doorMainLevelTexture, (Vector2){ doorMainLevel.x ,
                  doorMainLevel.y}, 0.0, 5.0, WHITE);
    //DrawRectangle(doorMainLevel.x, doorMainLevel.y, doorMainLevel.width, doorMainLevel.height, WHITE);

}

void update_main_level(void) {
    movement(&characer, &stock);
    Jump(&characer, &stock, platform);
//    if (isDoorUnlock()) {
//        CloseWindow();
//    }
    if (isWalking) {
        double time = GetTime() * 10;
        if (direction == -1) {
            // if player moves left
            if (((int)time) % 2 == 0) {
                characterTexture = char_walk1_left_level2;
            } else {
                characterTexture = char_walk2_left_level2;
            }
        } else {
            // if player moves right
            if (((int)time) % 2 == 0) {
                characterTexture = char_walk1_right_level2;

            } else {
                characterTexture = char_walk2_right_level2;
            }
        }
        isWalking = false;
    } else {
        // if player dont move
        if (direction == -1) {
            characterTexture = char_stand_left_level2;
        } else {
            characterTexture = char_stand_right_level2;
        }
    }

}
void unload_main_level(void) {
    UnloadTexture(main_bg);
    UnloadTexture(characterTexture);
    UnloadTexture(platformTexture);
    UnloadTexture(char_walk1_left_level2);
    UnloadTexture(char_walk2_left_level2);
    UnloadTexture(char_walk1_right_level2);
    UnloadTexture(char_walk2_right_level2);
    UnloadTexture(char_stand_left_level2);
    UnloadTexture(char_stand_right_level2);
}

bool isAllMissionDone(void) {
    return MISSIONS_DONE;
}

bool isDoorUnlock(void) {
    if (CheckCollisionRecs(characer, doorMainLevel)) {
        if (MISSIONS_DONE) {
            if (IsKeyPressed(KEY_E)) {
                return true;
            }
        }
        characer.x = doorMainLevel.x - characer.width;
    }
    return false;
}
