
#include "snake_game.h"

#include <stdlib.h>

int main(void) {
    Node* head = nullptr;
    Node* tail = nullptr;

    return 0;
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