#include "stack.h"

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int x, int y) {
    if (s->top < MAX - 1) {
        s->points[++(s->top)] = (Point){x, y};
    }
}

Point pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->points[(s->top)--];
    }
    return (Point){-1, -1}; // Return an invalid point if stack is empty
}
