#include <stdio.h>
#include <stdbool.h>
#include <conio.h> 
#include <windows.h>
#include <time.h>

#define SIZE 10
#define NUM_LEVELS 3 // Number of levels in the game

// ANSI color codes
#define ANSI_COLOR_BLACK     "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE "\x1b[37m"
#define ANSI_BACKGROUND_COLOR_BLACK "\x1b[40m"
#define ANSI_BACKGROUND_COLOR_RED "\x1b[41m"
#define ANSI_BACKGROUND_COLOR_GREEN "\x1b[42m"
#define ANSI_BACKGROUND_COLOR_YELLOW "\x1b[43m"
#define ANSI_BACKGROUND_COLOR_BLUE "\x1b[44m"
#define ANSI_BACKGROUND_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_COLOR_CYAN "\x1b[46m"
#define ANSI_BACKGROUND_COLOR_WHITE "\x1b[47m"

#define ANSI_COLOR_RESET   "\x1b[0m"

#define SIZE 10

// Function to set cursor position in console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to print the maze
void printMaze(int maze[SIZE][SIZE], int playerX, int playerY) {
    gotoxy(0, 0); // Set cursor position to the top-left corner of the console
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == playerY && j == playerX) {
                printf(ANSI_COLOR_CYAN "P " ANSI_COLOR_RESET); // Player marker
            } else if (maze[i][j] == 1) {
                printf(ANSI_COLOR_GREEN "# " ANSI_COLOR_RESET); // Wall
            } else {
                printf("  "); // Empty space
            }
        }
        printf("\n");
    }

    // Display control instructions under the game screen
    gotoxy(0, SIZE + 2);
    printf(ANSI_COLOR_MAGENTA "Controls:\n");
    printf("W - Move Up\n");
    printf("S - Move Down\n");
    printf("A - Move Left\n");
    printf("D - Move Right\n");
    printf("Q - Quit\n" ANSI_COLOR_RESET);
}

// Function to play the game
void playMazeGame(int maze[SIZE][SIZE], int level) {
    int playerX = 0, playerY = 0;
    int exitX = SIZE - 1, exitY = SIZE - 1;

    while (playerX != exitX || playerY != exitY) {
        printMaze(maze, playerX, playerY);

        char move = getch();

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

    printf(ANSI_COLOR_YELLOW "Congratulations! You reached the exit of level %d!\n"ANSI_COLOR_RESET , level + 1 );
    getch();
    system("cls");
}

int main() {
    PlaySound(TEXT("welcome.wav"), NULL, SND_FILENAME);
    system("cls");
    printf(ANSI_COLOR_RED "Now Loading" ANSI_COLOR_RESET);
    Sleep(500);
    printf(ANSI_COLOR_YELLOW ". " ANSI_COLOR_RESET);
    Sleep(500);
    printf(ANSI_COLOR_GREEN ". " ANSI_COLOR_RESET);
    Sleep(500);
    printf(ANSI_COLOR_MAGENTA ". " ANSI_COLOR_RESET);
    Sleep(500);
    printf(ANSI_COLOR_BLUE ". " ANSI_COLOR_RESET);
    Sleep(500);
    printf(".\n");

    system("cls");
    printf(ANSI_COLOR_RED "Welcome to the Maze Game!\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "Press any key to start..." ANSI_COLOR_RESET);

    getch(); // wait for a key press
    system("cls"); // clear the system output
    PlaySound(TEXT("Start.wav"), NULL, SND_FILENAME);
    PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    int levels[NUM_LEVELS][SIZE][SIZE] = {
        { // Level 1
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
        },
        { // Level 2
            {0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
        },
        { // Level 3
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
        }
    };

    for (int i = 0; i < NUM_LEVELS; i++) {
        playMazeGame(levels[i], i);
        system("cls");
    }

    printf(ANSI_COLOR_CYAN "Congratulations! You have completed all levels!\n" ANSI_COLOR_RESET);
    PlaySound(TEXT("Welldone.wav"), NULL, SND_FILENAME);
    PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME);

    return 0;
}
