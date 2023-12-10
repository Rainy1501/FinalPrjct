#include <stdio.h>
#include <stdbool.h>
#include <conio.h> 
#include <windows.h>
#include <time.h>
#include <string.h>

#define SIZE 10
#define NUM_LEVELS 10 // Number of levels in the game
#define MAX_PLAYERS 20 // Maximum number of players on the leaderboard

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

typedef struct {
	char playerName[30];
	int score;
} Player; 

void displayMainMenu() {
    system("cls");
    printf(ANSI_COLOR_CYAN "Welcome to the Maze Game!\n" ANSI_COLOR_RESET);
    printf("1. Play\n");
    printf("2. View Leaderboard\n");
    printf("3. Exit\n");
}

// Function to set cursor position in console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to print the maze
void printMaze(int maze[SIZE][SIZE], int playerX, int playerY, int score) {
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
    
    // Display score
    printf("\nScore: %d\n", score);
}

// Function to play the game
void playMazeGame(int maze[SIZE][SIZE], int level, int* totalScore) {
    int playerX = 0, playerY = 0;
    int exitX = SIZE - 1, exitY = SIZE - 1;
    int moves = 0; // Variable to count moves
    int score = 0; // Initialize score
    clock_t startTime = clock(); // Start time

    while (playerX != exitX || playerY != exitY) {
        printMaze(maze, playerX, playerY, *totalScore); // Display the maze and current score

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
            moves++; // Increment move count on valid move
        }
    }
	
	clock_t endTime = clock(); // End time
    double timeTaken = ((double)(endTime - startTime)) / CLOCKS_PER_SEC; // Calculate time taken in seconds

    printf(ANSI_COLOR_YELLOW "Congratulations! You reached the exit of level %d!\n"ANSI_COLOR_RESET , level + 1 );
    printf("Total moves: %d\n", moves);
	printf("Time taken: %.2f seconds\n" ANSI_COLOR_RESET, timeTaken);
	
    // Calculate score based on time and moves (a simple formula)
    score = 1000 - (moves * 10) - (int)(timeTaken * 10);
    if (score < 0) {
        score = 0; // Ensure the score is non-negative
    }
    printf("Your score for level %d: %d\n", level + 1, score);
    
    // Add current level's score to the total score
    *totalScore += score;

    // Pass the score to the printMaze function
    printMaze(maze, playerX, playerY, *totalScore);

    getch();
    system("cls");
}

// Function to display leaderboard
void displayLeaderboard(Player leaderboard[]) {
    system("cls");
    printf(ANSI_COLOR_YELLOW "*** Leaderboard ***\n\n");
    printf("Rank\tPlayer Name\tScore\n");

    for (int i = 0; i < MAX_PLAYERS; i++) {
        printf("%d.\t%s\t\t%d\n", i + 1, leaderboard[i].playerName, leaderboard[i].score);
    }
}

void saveLeaderboard(Player leaderboard[]) {
    FILE *file;
    file = fopen("leaderboard.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < MAX_PLAYERS; i++) {
            fprintf(file, "%s %d\n", leaderboard[i].playerName, leaderboard[i].score);
        }
        fclose(file);
    } else {
        printf("Error opening file for writing.\n");
    }
}

// Function to load the leaderboard from a file
void loadLeaderboard(Player leaderboard[]) {
    FILE *file;
    file = fopen("leaderboard.txt", "r");
    if (file != NULL) {
        for (int i = 0; i < MAX_PLAYERS; i++) {
            fscanf(file, "%s %d\n", leaderboard[i].playerName, &leaderboard[i].score);
        }
        fclose(file);
    } else {
        printf("File does not exist or could not be opened.\n");
    }
}



int main() {
	int totalScore = 0; // Initialize total score
	Player leaderboard[MAX_PLAYERS] = { 0 }; // Initialize leaderboard array
	loadLeaderboard(leaderboard); // Load the previous leaderboard

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

    int choice;
    do {
        displayMainMenu();
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1:
                system("cls");
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
                },
                    { // Level 4
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
                },
                    { // Level 5
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
                },
                    { // Level 6
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
                },
                    { // Level 7
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
                },
                    { // Level 8
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
                },
                    { // Level 9
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
                },
                    { // Level 10
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
            playMazeGame(levels[i], i, &totalScore);
            system("cls");
        }

        printf(ANSI_COLOR_CYAN "Congratulations! You have completed all levels!\n" ANSI_COLOR_RESET);
        printf("Total Score for all levels: %d\n", totalScore);
        PlaySound(TEXT("Welldone.wav"), NULL, SND_FILENAME);
        PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME);
    
        printf("Enter your name for the leaderboard: ");
        char playerName[50];
        fgets(playerName, sizeof(playerName), stdin);
        playerName[strcspn(playerName, "\n")] = '\0'; // Remove the newline character from playerName
    
        // Find the position to insert the current player's score
        int insertPosition = -1;
        for (int i = MAX_PLAYERS - 1; i >= 0; i--) {
            if (totalScore > leaderboard[i].score) {
                insertPosition = i;
            }
        }
    
        // Shift the existing scores to make space for the current player's score
        if (insertPosition != -1) {
            for (int i = MAX_PLAYERS - 1; i > insertPosition; i--) {
                strcpy(leaderboard[i].playerName, leaderboard[i - 1].playerName);
                leaderboard[i].score = leaderboard[i - 1].score;
            }
            strcpy(leaderboard[insertPosition].playerName, playerName);
            leaderboard[insertPosition].score = totalScore;
        }
    
        displayLeaderboard(leaderboard); // Display the leaderboard after adding the player's score
        saveLeaderboard(leaderboard); // Save the updated leaderboard to the fil
                break;
            case 2:
                displayLeaderboard(leaderboard);
                printf("\nPress any key to return to the main menu...");
                getch();
                break;
            case 3:
                printf("Exiting the game...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 3.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}