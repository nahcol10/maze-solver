#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "point.h"

#define MAX 100

int maze[MAX][MAX];
int visited[MAX][MAX] = {0};
int rows, cols;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int isValid(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0 && !visited[x][y]);
}

int dfs(int startX, int startY, int endX, int endY) {
    Stack s;
    initStack(&s);
    push(&s, startX, startY);
    visited[startX][startY] = 1;

    while (!isEmpty(&s)) {
        Point p = pop(&s);
        int x = p.x;
        int y = p.y;

        if (x == endX && y == endY) {
            return 1; // Path found
        }

        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];

            if (isValid(newX, newY)) {
                visited[newX][newY] = 1;
                push(&s, newX, newY);
            }
        }
    }

    return 0; // No path found
}

int main() {
    printf("Enter the dimensions of the maze (rows, cols): ");
    scanf("%d %d", &rows, &cols);

    printf("Enter the maze grid (0 for open path, 1 for wall):\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &maze[i][j]);

    int startX, startY, endX, endY;
    printf("Enter the start point (x y): ");
    scanf("%d %d", &startX, &startY);
    printf("Enter the end point (x y): ");
    scanf("%d %d", &endX, &endY);

    if (dfs(startX, startY, endX, endY)) {
        printf("Path found using DFS.\n");
    } else {
        printf("No path found using DFS.\n");
    }

    return 0;
}
