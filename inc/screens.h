#ifndef SCREENS_H
#define SCREENS_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

enum GameScreen {
    MENU,
    MENU_ABOUT,
    LEVEL_ONE,
    LEVEL_TWO,
    LEVEL_THREE,
};

typedef struct s_button {
    Rectangle rect;
    Color color;
    char *text;

} Button;

typedef struct Button {
    Rectangle rect;
    Texture2D texture;
    Color color;
} ButtonFinish;

extern int exit_game;
extern enum GameScreen current_screen;

void init_menu_screen(void);
void draw_menu_screen(void);
void update_menu_screen(void);
void unload_menu_screen(void);
int finish_menu_screen(void);

void init_about_screen(void);
void draw_about_screen(void);
void update_about_screen(void);
void unload_about_screen(void);
int finish_about_screen(void);

void init_level1_screen(void);
void draw_level1_screen(void);
bool check_puzzle_completion_lvl1(int result);
void update_level1_screen(void);
void unload_level1_screen(void);
int finish_level1_screen(void);

void init_finish_screen(void);
void draw_finish_screen(void);
void update_finish_screen(void);
void unload_finish_screen(void);
int finish_last_screen(void);

void init_main_level(void);
void draw_main_level(void);
void update_main_level(void);
void unload_main_level(void);
bool isDoorUnlock(void);
bool isAllMissionDone(int result);

void draw_player(void);
void draw_player_lvl2(void);
#endif
