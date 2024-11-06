#include <stdio.h>
#include "queue.h"
#include "point.h"

#define MAX 100

int maze[MAX][MAX];
int visited[MAX][MAX] = {0};
int rows, cols;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Helper function to print a path
void printPath(Point path[], int length) {
    for (int i = 0; i < length; i++) {
        printf("(%d, %d) ", path[i].x, path[i].y);
    }
    printf("\n");
}

// BFS function to find and print all paths from start to end
void bfs_maze_solver(int startX, int startY, int endX, int endY) {
    Queue q;
    initQueue(&q);

    // Initialize the first path with the start position
    Point startPath[MAX];
    startPath[0] = (Point){startX, startY};
    enqueue(&q, startX, startY);
    visited[startX][startY] = 1;

    // Array to keep paths for each position in the queue
    Point paths[MAX * MAX][MAX];  // Reduced to avoid overflow
    int pathLengths[MAX * MAX] = {0}; 
    pathLengths[0] = 1;
    paths[0][0] = (Point){startX, startY};

    int pathIndex = 1;

    // Process the queue
    while (!isEmpty(&q)) {
        // Dequeue the current point
        Point current = dequeue(&q);
        int x = current.x;
        int y = current.y;

        // Get the path length and current path for this point
        int pathLength = pathLengths[pathIndex - 1];
        Point currentPath[MAX];
        for (int i = 0; i < pathLength; i++) {
            currentPath[i] = paths[pathIndex - 1][i];
        }

        // If we reach the destination, print the path
        if (x == endX && y == endY) {
            printPath(currentPath, pathLength);
            continue;
        }

        // Explore all 4 possible directions
        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];

            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                maze[newX][newY] == 0 && !visited[newX][newY]) {
                
                // Copy current path and add new point to it
                Point newPath[MAX];
                for (int j = 0; j < pathLength; j++) {
                    newPath[j] = currentPath[j];
                }
                newPath[pathLength] = (Point){newX, newY};

                // Enqueue the new point and path, update visited status
                enqueue(&q, newX, newY);
                visited[newX][newY] = 1;
                pathLengths[pathIndex] = pathLength + 1;
                
                // Copy new path to paths array
                for (int j = 0; j <= pathLength; j++) {
                    paths[pathIndex][j] = newPath[j];
                }
                pathIndex++;
            }
        }
    }
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

    printf("All possible paths from source to destination using BFS:\n");
    bfs_maze_solver(startX, startY, endX, endY);

    return 0;
}
