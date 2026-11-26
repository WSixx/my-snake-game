#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <stddef.h>

typedef struct node {
    char body;
    int x, y;
    struct node* prev;
    struct node* next;
} Node;

typedef struct Board {
    int width;
    int height;
    char* cells;
} Board;

[[nodiscard]] bool push_head(Node** head, Node** tail, int x, int y, char body);
void pop_tail(Node** head, Node** tail);

// board
[[nodiscard]] bool board_init(Board* board, int width, int height);
void board_set(Board* board, int x, int y, char c);
[[nodiscard]] char board_get(const Board* board, int x, int y);
void board_clear(Board* board);
void board_free(Board* board);

// terminal
[[nodiscard]] bool enable_raw_mode(struct termios* orig_termios);

// utils
[[nodiscard]] bool isBoardNull(const Board* board);
[[nodiscard]] bool isBoardCoordinatesValid(const Board* board, int x, int y);

#endif
