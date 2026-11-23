
#include "snake_game.h"

#include <stddef.h>
#include <stdlib.h>

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