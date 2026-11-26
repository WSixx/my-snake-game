
#include "snake_game.h"

#include <stddef.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Lembrar
// next aponta para trás (da cabeça rumo à cauda)
// prev aponta para frente (da cauda rumo à cabeça)

int main(void) {
    Node* head = nullptr;
    Node* tail = nullptr;

    return 0;
}

[[nodiscard]] bool board_init(Board* board, int width, int height) {
    if (width <= 0 || height <= 0 || board == nullptr) {
        return false;
    }

    size_t newSize = (size_t)width * (size_t)height;
    // alocando e ja zerando
    char* new_cells = calloc(newSize, sizeof(*new_cells));

    if (new_cells == nullptr) {
        return false;
    }
    board->width = width;
    board->height = height;
    board->cells = new_cells;
    return true;
}

void board_set(Board* board, int x, int y, char c) {
    if (isBoardNull(board)) {
        return;
    }
    if (!isBoardCoordinatesValid(board, x, y)) {
        return;
    }
    *(board->cells + (y * board->width) + x) = c;
}

[[nodiscard]] char board_get(const Board* board, int x, int y) {
    if (isBoardNull(board)) {
        return '\0';
    }
    if (!isBoardCoordinatesValid(board, x, y)) {
        return '\0';
    }

    return *(board->cells + (y * board->width) + x);
}

void board_clear(Board* board) {
    if (isBoardNull(board)) {
        return;
    }
    for (int y = 0; y <= board->height - 1; y++) {
        for (int x = 0; x <= board->width - 1; x++) {
            if (y == board->height - 1 || x == board->width - 1 || y == 0 || x == 0) {
                board_set(board, x, y, '#');
                continue;
            }
            board_set(board, x, y, ' ');
        }
    }
}

void board_free(Board* board) {
    if (board == nullptr) {
        return;
    }
    // board está na stack...
    free(board->cells);
    board->cells = nullptr;
}

[[nodiscard]] bool push_head(Node** head, Node** tail, int x, int y, char body) {
    Node* nodePtr;
    nodePtr = malloc(sizeof(*nodePtr));
    if (nodePtr == nullptr) {
        return false;
    }
    nodePtr->x = x;
    nodePtr->y = y;
    nodePtr->body = body;
    nodePtr->prev = nullptr;
    nodePtr->next = nullptr;

    if (*head == nullptr) {  // lista vazia
        *head = nodePtr;
        *tail = nodePtr;
    } else {
        nodePtr->next = *head;
        (*head)->prev = nodePtr;
        *head = nodePtr;
    }

    return true;
}

void pop_tail(Node** head, Node** tail) {
    if (*tail == nullptr) {  // lista vazia
        return;
    }
    Node* oldTail = *tail;
    *tail = oldTail->prev;
    if (*tail == nullptr) {
        *head = nullptr;
    } else {
        (*tail)->next = nullptr;
    }
    free(oldTail);
}

[[nodiscard]] bool enable_raw_mode(struct termios* orig_termios) {
    if (orig_termios == nullptr) {
        return false;
    }
    if (tcgetattr(STDIN_FILENO, orig_termios) == -1) {
        return false;
    }

    // copia na stack
    struct termios raw = *orig_termios;
    // zerandp os bits do echo e icanon
    raw.c_lflag &= ~(ECHO | ICANON);  // ICANON -> enter

    // controlam quando read() retorna
    // leitura não bloqueante (polling);
    raw.c_cc[VMIN] = 0;   // numero minimo de bytes de espera até retornar 0
    raw.c_cc[VTIME] = 0;  // tempo de espera ate retornar 0

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        return false;
    }

    return true;
}

[[nodiscard]] bool isBoardCoordinatesValid(const Board* board, int x, int y) {
    if (x < 0 || y < 0 || x > board->width - 1 || y > board->height - 1) {
        return true;
    }
    return false;
}

[[nodiscard]] bool isBoardNull(const Board* board) {
    if (board == nullptr || board->cells == nullptr) {
        return true;
    }
    return false;
}