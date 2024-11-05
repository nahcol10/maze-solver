#ifndef STACK_H
#define STACK_H

#include "point.h"

#define MAX 100

typedef struct {
    Point points[MAX];
    int top;
} Stack;

void initStack(Stack *s);
int isEmpty(Stack *s);
void push(Stack *s, int x, int y);
Point pop(Stack *s);

#endif // STACK_H
