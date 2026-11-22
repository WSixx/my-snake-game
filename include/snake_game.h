#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <stddef.h>

typedef struct node {
    char body;
    int x, y;
    struct node* prev;
    struct node* next;
} Node;

[[nodiscard]] bool push_head(Node** head, Node** tail, int x, int y, char body);

#endif
