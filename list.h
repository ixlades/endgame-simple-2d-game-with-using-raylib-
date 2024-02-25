#ifndef LIST_H
#define LIST_H

#include <raylib.h>

typedef struct s_list{
    void *data;
    struct s_list *next;
} t_list;

typedef struct s_size{
    int widthX;
    int heightY;
    char *meze_res;
} Size;








#endif
