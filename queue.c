#include "queue.h"

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

void enqueue(Queue *q, int x, int y) {
    if (q->rear < MAX * MAX) {
        q->points[q->rear++] = (Point){x, y};
    }
}

Point dequeue(Queue *q) {
    if (!isEmpty(q)) {
        return q->points[q->front++];
    }
    return (Point){-1, -1}; // Return an invalid point if queue is empty
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}
