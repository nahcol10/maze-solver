#ifndef QUEUE_H
#define QUEUE_H

#include "point.h"

#define MAX 100

typedef struct {
    Point points[MAX * MAX];
    int front, rear;
} Queue;

void enqueue(Queue *q, int x, int y);
Point dequeue(Queue *q);
int isEmpty(Queue *q);
void initQueue(Queue *q);

#endif // QUEUE_H
