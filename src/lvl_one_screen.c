#include "raylib.h"
#include "../inc/player.h"
#include "../inc/inventory.h"
#include "../inc/movement.h"

Texture2D background_texture_lvl1;
Image char_stand_img;
Texture2D char_stand_right;
Texture2D char_stand_left;
Image char_walk1_img;
Texture2D char_walk1_right;
Texture2D char_walk1_left;
Image char_walk2_img;
Texture2D char_walk2_right;
Texture2D char_walk2_left;
SizeData stock_lvl1 = {0};

Texture wall;
Vector2 wall_pos;

Vector2 background_pos;
Vector2 background_pos1;
Texture2D exit_door_lvl1;

static int finish_lvl_one_screen = 0;
static int lvl_one_finished;

bool check_puzzle_completion_lvl1(int result) {
    if (result == 1) {
        lvl_one_finished = 1;
        return true;   
    }
    return false;

}

void init_level1_screen(void) {
   
    background_texture_lvl1 = LoadTexture("resource/level_one_bg.png");
    exit_door_lvl1 = LoadTexture("resource/door_lvl_1.png");
    wall = LoadTexture("C:/Users/38097/Desktop/rep_4/resource/wall.png");
    wall_pos.x = 0;
    wall_pos.y = 0;

    background_pos.x = 0;
    background_pos.y = 0;
    background_pos1.x = 1008;
    background_pos1.y = 0;
    // load images for player anim
    char_stand_img = LoadImage("resource/player.png");
    char_stand_right = LoadTextureFromImage(char_stand_img);
    ImageFlipHorizontal(&char_stand_img);
    char_stand_left = LoadTextureFromImage(char_stand_img);
    
    char_walk1_img = LoadImage("resource/walk1.png");
    char_walk1_right = LoadTextureFromImage(char_walk1_img);
    ImageFlipHorizontal(&char_walk1_img);
    char_walk1_left = LoadTextureFromImage(char_walk1_img);
    
    char_walk2_img = LoadImage("resource/walk2.png");
    char_walk2_right = LoadTextureFromImage(char_walk2_img);
    ImageFlipHorizontal(&char_walk2_img);
    char_walk2_left = LoadTextureFromImage(char_walk2_img);

    stock_lvl1.speedX = 10.0f;
    stock_lvl1.speedY = 1.0f;
    stock_lvl1.screenWidth = GetScreenWidth();
    stock_lvl1.screenHeight = GetScreenHeight();
    stock_lvl1.jumpForce = 15;
    stock_lvl1.gravity = 0.5f;
    player.texture = LoadTexture("resource/player.png");
    player.pos = (Vector2){410, 500};
    player.isWalking = false;
    player.direction = 0;
    finish_lvl_one_screen = 0;
    lvl_one_finished = 0;
    
}

void update_level1_screen(void) {
    
    movement_lvl1(&player.pos, &stock_lvl1, player.texture.width);
    // player anim logic
    if (player.isWalking) {
        double time = GetTime() * 10;
        if (player.direction == -1) {
            // if player moves left
            if (((int)time) % 2 == 0) {
                player.texture = char_walk1_left;
            } else {
                player.texture = char_walk2_left;
            }
        } else {
            // if player moves right
            if (((int)time) % 2 == 0) {
                player.texture = char_walk1_right;
                
            } else {
                player.texture = char_walk2_right;
            }
        }
        player.isWalking = false;
    } else {
        // if player dont move
        if (player.direction == -1) {
            player.texture = char_stand_left;
        } else {
            player.texture = char_stand_right;
        }

    }

    if (player.pos.x <= 90 && player.pos.y == 500 && lvl_one_finished) {
        finish_lvl_one_screen = 1;
    }
    
}

void draw_level1_screen(void) {
    DrawTextureEx(background_texture_lvl1, background_pos1, 0.0, 3.5, WHITE);
    DrawTextureEx(background_texture_lvl1, background_pos, 0.0, 3.5, WHITE);
    DrawTextureEx(exit_door_lvl1,(Vector2){50,550},0.0f,5.0f,WHITE);
}

void draw_player(void) {
    DrawTextureEx(player.texture, player.pos, 0.0, 6.0, WHITE);
}

void unload_level1_screen(void) {
    // UnloadTexture(player.texture);
    UnloadImage(char_stand_img);
    UnloadImage(char_walk1_img);
    UnloadImage(char_walk2_img);
    UnloadTexture(exit_door_lvl1);
    UnloadTexture(background_texture_lvl1);
    UnloadTexture(char_stand_right);
    UnloadTexture(char_stand_left);
    UnloadTexture(char_walk1_right);
    UnloadTexture(char_walk1_left);
    UnloadTexture(char_walk2_right);
    UnloadTexture(char_walk2_left);

}

int finish_level1_screen(void) {
    return finish_lvl_one_screen;
}
