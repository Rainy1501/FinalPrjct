#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define SIZE 10

// Function to print the maze in the window
void printMazeInWindow(HDC hdc, int maze[SIZE][SIZE], int playerX, int playerY) {
    int cellWidth = 40; // Width of each cell
    int cellHeight = 40; // Height of each cell

    // Set colors for maze elements
    COLORREF wallColor = RGB(0, 0, 0); // Black for walls
    COLORREF emptySpaceColor = RGB(255, 255, 255); // White for empty spaces
    COLORREF playerColor = RGB(0, 0, 255); // Blue for player marker

    // Draw maze in the window
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            RECT rect = { j * cellWidth, i * cellHeight, (j + 1) * cellWidth, (i + 1) * cellHeight };

            // Set colors based on maze elements
            COLORREF cellColor;
            if (i == playerY && j == playerX) {
                cellColor = playerColor;
            } else if (maze[i][j] == 1) {
                cellColor = wallColor;
            } else {
                cellColor = emptySpaceColor;
            }

            // Fill rectangle with the appropriate color
            HBRUSH brush = CreateSolidBrush(cellColor);
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);
        }
    }
}

// Function to get the key pressed for movement
char getMovementInput() {
    if (GetAsyncKeyState('W') & 0x8000) {
        return 'W';
    } else if (GetAsyncKeyState('S') & 0x8000) {
        return 'S';
    } else if (GetAsyncKeyState('A') & 0x8000) {
        return 'A';
    } else if (GetAsyncKeyState('D') & 0x8000) {
        return 'D';
    } else if (GetAsyncKeyState('Q') & 0x8000) {
        return 'Q';
    }
    return '\0'; // No movement key pressed
}

// Function to play the maze game within the window
void playMazeGame(HWND hwnd, HDC hdc, int maze[SIZE][SIZE]) {
    int playerX = 0, playerY = 0; // Starting position of the player
    int exitX = SIZE - 1, exitY = SIZE - 1; // Exit position
    bool gameWon = false; // Flag to track if the game is won

    MSG msg;
    while (!gameWon) {
        if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Draw the maze in the window
        printMazeInWindow(hdc, maze, playerX, playerY);

        // Handle keyboard input
        char move = getMovementInput();

        int newX = playerX, newY = playerY;

        switch (move) {
            case 'W':
            case 'w':
                newY = playerY - 1;
                break;
            case 'S':
            case 's':
                newY = playerY + 1;
                break;
            case 'A':
            case 'a':
                newX = playerX - 1;
                break;
            case 'D':
            case 'd':
                newX = playerX + 1;
                break;
            case 'Q':
            case 'q':
                printf("Quitting the game...\n");
                PostQuitMessage(0);
                break;
            default:
                break;
        }

        // Check if the new position is within bounds and is a valid move
        if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && maze[newY][newX] == 0) {
            playerX = newX;
            playerY = newY;
        }

        // Check if the player reached the exit
        if (playerX == exitX && playerY == exitY) {
            gameWon = true;
        }
    }

    if (gameWon) {
        MessageBox(hwnd, "Congratulations! You reached the exit!", "Victory!", MB_OK | MB_ICONINFORMATION);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);

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

            playMazeGame(hwnd, hdc, maze);

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main() {
    // Register window class
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "MazeGameWindow";
    RegisterClass(&wc);

    // Create window
    HWND hwnd = CreateWindowEx(
        0,
        "MazeGameWindow",
        "Maze Game",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        SIZE * 40, // Adjust the window size based on maze dimensions
        SIZE * 40 + 40, // Add extra height for text/console
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    // Display window
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
