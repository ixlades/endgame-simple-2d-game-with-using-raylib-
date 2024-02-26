#ifndef SCREENS_H
#define SCREENS_H

enum GameScreen
{
    MENU
};

typedef struct s_button
{
    Rectangle rect;
    Color color;
    char *text;

} Button;

void init_menu_screen(void);
void draw_menu_screen(void);
#endif
