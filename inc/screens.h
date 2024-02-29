#ifndef SCREENS_H
#define SCREENS_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

enum GameScreen
{
    MENU,
    MENU_ABOUT,
    LEVEL_ONE
};

typedef struct s_button
{
    Rectangle rect;
    Color color;
    char *text;

} Button;

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
#endif
