#include <stdio.h>
#include "point.h"

#define MAX 100

int maze[MAX][MAX];
int visited[MAX][MAX] = {0};
int rows, cols;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void printPath(Point path[], int length) {
    for (int i = 0; i < length; i++) {
        printf("(%d, %d) ", path[i].x, path[i].y);
    }
    printf("\n");
}

int isValid(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0 && !visited[x][y]);
}

void dfs_maze_solver(int x, int y, int endX, int endY, Point path[], int pathIndex) {
    // Mark the current cell as visited and add it to the path
    visited[x][y] = 1;
    path[pathIndex].x = x;
    path[pathIndex].y = y;
    pathIndex++;

    // Check if we have reached the destination
    if (x == endX && y == endY) {
        printPath(path, pathIndex); // Print the current complete path
    } else {
        // Explore all 4 directions
        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];

            if (isValid(newX, newY)) {
                dfs_maze_solver(newX, newY, endX, endY, path, pathIndex);
            }
        }
    }

    // Backtrack: unmark the current cell as visited
    visited[x][y] = 0;
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

    Point path[MAX * MAX]; // Maximum possible path length
    printf("All possible paths from source to destination:\n");
    dfs_maze_solver(startX, startY, endX, endY, path, 0);

    return 0;
}
