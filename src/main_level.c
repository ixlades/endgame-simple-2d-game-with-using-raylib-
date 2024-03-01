#include "../inc/main_level.h"
#include "../inc/player.h"

Texture2D hint_e_texture;
Window hint_e_door;

int direction = 0;
bool isWalking = false;

Texture2D main_bg;
Texture2D platformTexture;
Texture2D platformTextureSmall;
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
bool finish_main_level;
int all_tasks_completed;
SizeData stock1;

void init_main_level(void) {
    main_bg = LoadTexture("resource/background_lvl2.png");
    platformTexture = LoadTexture("resource/platform1.png");
    platformTextureSmall = LoadTexture("resource/platform2.png");
    characterTexture = LoadTexture("resource/player.png");
    doorMainLevelTexture = LoadTexture("resource/door_locked.png");

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

    //---------------------------Stock1------------------------------------
    stock1.screenHeight = GetScreenHeight();
    stock1.screenWidth = GetScreenWidth();
    stock1.speedX = 10.0f;
    stock1.speedY = 0.0f;
    stock1.jumpForce = 6.5f;
    stock1.gravity = 0.1f;
    finish_main_level = false;
    all_tasks_completed = 1;
    //---------------------------Character------------------------------------
    characer = (Rectangle){ 100, 700 , (characterTexture.width * 2) - 7 , (characterTexture.height * 3) - 13};

    //---------------------------Platforms------------------------------------
    platform[0] = (Rectangle){ 1280 - platformTexture.width, 250 + platformTexture.height,
                               platformTexture.width, platformTexture.height };
    platform[1] = (Rectangle){ 0, 270 + platformTexture.height,
                               platformTexture.width, platformTexture.height };
    platform[2] = (Rectangle){ 0, 515,
                               platformTexture.width, platformTexture.height };
    platform[3] = (Rectangle){ 210 + platformTexture.width, 400 + platformTexture.height,
                               platformTexture.width, platformTexture.height };
    platform[4] = (Rectangle){ 650 + platformTextureSmall.width, 340 + platformTextureSmall.height,
                               platformTextureSmall.width, platformTextureSmall.height };
    //------------------------------Door-----------------------------------
    doorMainLevel = (Rectangle){ 1280 - doorMainLevelTexture.width * 3.5, 260 + platformTexture.height - doorMainLevelTexture.height * 4,
                                 doorMainLevelTexture.width * 4 , doorMainLevelTexture.height * 5 };

    //------------------------------Hint----------------------------
    hint_e_texture = LoadTexture("resource/hint_E.png");
}

void draw_platforms(void) {
    for (int i = 0; i < NUM_OF_PLATFORMS - 1; ++i) {
        DrawTexture(platformTexture, platform[i].x, platform[i].y, WHITE);
    }
    DrawTexture(platformTextureSmall, platform[4].x, platform[4].y,WHITE);
}

void draw_main_level(void) {
    // DrawTexturePro(
    //         main_bg,
    //         (Rectangle){0.0f, 0.0f, (float)main_bg.width,
    //                     (float)-main_bg.height},
    //         (Rectangle){0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT},
    //         (Vector2){0, 0}, 0.0f, BROWN);
    DrawTextureEx(main_bg, (Vector2) {0, 0}, 0 , 4.5, WHITE);
    draw_platforms();
    // DrawTextureEx(characterTexture, (Vector2){characer.x - characer.width - 10,
    //                                        characer.y - characer.height }, 0.0, 6.0, WHITE);
    DrawTextureEx(doorMainLevelTexture, (Vector2){ doorMainLevel.x ,
                  doorMainLevel.y}, 0.0, 3.5, WHITE);
    if (CheckCollisionRecs(characer, platform[0])) {
        if (all_tasks_completed) {
            DrawTextureEx(hint_e_texture, (Vector2) {doorMainLevel.x -30 + doorMainLevel.width / 2,
                                        doorMainLevel.y - 60 }, 0, 4, WHITE);
        }
    }
   // DrawRectangle(characer.x, characer.y, characer.width, characer.height, WHITE);
}

void draw_player_lvl2(void) {
    DrawTextureEx(characterTexture, (Vector2) { characer.x - characer.width - 10, characer.y - characer.height}, 0.0, 6.0, WHITE);
}

void update_main_level(void) {
    movement(&characer, &stock1);
    Jump(&characer, &stock1, platform);

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
    UnloadTexture(platformTextureSmall);
    UnloadTexture(char_walk1_left_level2);
    UnloadTexture(char_walk2_left_level2);
    UnloadTexture(char_walk1_right_level2);
    UnloadTexture(char_walk2_right_level2);
    UnloadTexture(char_stand_left_level2);
    UnloadTexture(char_stand_right_level2);
}

bool isAllMissionDone(void) {
    return all_tasks_completed;
}

bool isDoorUnlock(void) {
    if (CheckCollisionRecs(characer, doorMainLevel)) {
        if (all_tasks_completed) {
            DrawTextureEx(hint_e_texture, (Vector2) { doorMainLevel.x - doorMainLevel.width / 2,
                                                   doorMainLevel.y }, 0, 4, WHITE);
            if (IsKeyPressed(KEY_E)) {
                finish_main_level = true;
                return finish_main_level;
            }
        }
        characer.x = doorMainLevel.x - characer.width;
    }
    return false;
}
