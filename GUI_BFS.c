#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "queue.h" // Use a queue instead of a stack
#include "point.h"

#define MAX 100
#define CELL_SIZE 40 // Adjust for clearer visualization on a 10x10 grid
#define WINDOW_WIDTH (8 * CELL_SIZE)
#define WINDOW_HEIGHT (8 * CELL_SIZE)

int maze[8][8] = {
    {0, 1, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 1, 0},
    {0, 0, 0, 1, 0, 0, 1, 0},
    {1, 1, 0, 0, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 1, 1, 1, 1, 0, 0}
};

int visited[MAX][MAX] = {0};
int rows = 10, cols = 10;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Initialize SDL variables
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int isValid(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0 && !visited[x][y]);
}

void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("BFS Maze Traversal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void cleanupSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderMaze(int endX, int endY) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White background
    SDL_RenderClear(renderer);

    // Draw maze grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // Black walls
            } else if (visited[i][j]) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); // Green path
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White open path
            }

            SDL_Rect cell = {j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_RenderFillRect(renderer, &cell);
        }
    }

    // Draw end point
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red for the end point
    SDL_Rect endCell = {endY * CELL_SIZE, endX * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_RenderFillRect(renderer, &endCell);

    SDL_RenderPresent(renderer);
    SDL_Delay(500); // Delay to visualize the traversal step-by-step
}

int bfs(int startX, int startY, int endX, int endY) {
    Queue q;
    initQueue(&q);
    enqueue(&q, startX, startY);
    visited[startX][startY] = 1;

    while (!isEmpty(&q)) {
        Point p = dequeue(&q);
        int x = p.x;
        int y = p.y;

        renderMaze(endX, endY); // Render the maze after each move

        if (x == endX && y == endY) {
            return 1; // Path found
        }

        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];

            if (isValid(newX, newY)) {
                visited[newX][newY] = 1;
                enqueue(&q, newX, newY);
            }
        }
    }

    return 0; // No path found
}

int main() {
    int startX = 0, startY = 0, endX = 7, endY = 7;

    initSDL();

    if (bfs(startX, startY, endX, endY)) {
        printf("Path found using BFS.\n");
    } else {
        printf("No path found using BFS.\n");
    }

    SDL_Delay(500);
    cleanupSDL();
    return 0;
}
