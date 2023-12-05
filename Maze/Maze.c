#include <stdio.h>
#include <stdbool.h>
#include <conio.h> // For getch() function (specific to certain environments like Windows)

#define SIZE 10

// Function to print the maze
void printMaze(int maze[SIZE][SIZE], int playerX, int playerY) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == playerY && j == playerX) {
                printf("P "); // Player marker
            } else if (maze[i][j] == 1) {
                printf("# "); // Wall
            } else {
                printf("  "); // Empty space
            }
        }
        printf("\n");
    }
}

// Function to play the game
void playMazeGame(int maze[SIZE][SIZE]) {
    int playerX = 0, playerY = 0; // Starting position of the player
    int exitX = SIZE - 1, exitY = SIZE - 1; // Exit position

    printf("Welcome to the Maze Game!\n");

    while (playerX != exitX || playerY != exitY) {
        printf("\n");
        printMaze(maze, playerX, playerY);

        char move = getch(); // Get a single character input

        int newX = playerX, newY = playerY;

        switch (move) {
            case 'W':
            case 'w':
                newY--;
                break;
            case 'S':
            case 's':
                newY++;
                break;
            case 'A':
            case 'a':
                newX--;
                break;
            case 'D':
            case 'd':
                newX++;
                break;
            case 'Q':
            case 'q':
                printf("Quitting the game...\n");
                return;
            default:
                printf("Invalid move!\n");
                continue;
        }

        if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && maze[newY][newX] == 0) {
            playerX = newX;
            playerY = newY;
        }
    }

    printf("Congratulations! You reached the exit!\n");
}

int main() {
    // Example maze level
    int maze[SIZE][SIZE] = {
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
    };

    playMazeGame(maze);

    return 0;
}