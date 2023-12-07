#include <stdio.h>

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

int main() {
    printf(ANSI_COLOR_BLACK "This text is black." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_RED "This text is red." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_GREEN "This text is green." ANSI_COLOR_RESET "\n");   
    printf(ANSI_COLOR_YELLOW "This text is yellow." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_BLUE "This text is blue." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_MAGENTA "This text is magenta." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_CYAN "This text is cyan." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_WHITE "This text is white." ANSI_COLOR_RESET "\n");
    printf(ANSI_BACKGROUND_COLOR_BLACK "Lorem ipsum dolor sit amet." ANSI_COLOR_RESET "\n");
    printf(ANSI_BACKGROUND_COLOR_RED "Lorem ipsum dolor sit amet." ANSI_COLOR_RESET "\n");
    printf(ANSI_BACKGROUND_COLOR_GREEN "Lorem ipsum dolor sit amet." ANSI_COLOR_RESET "\n");
    printf(ANSI_BACKGROUND_COLOR_YELLOW "Lorem ipsum dolor sit amet." ANSI_COLOR_RESET "\n");
    printf(ANSI_BACKGROUND_COLOR_BLUE "Lorem ipsum dolor sit amet." ANSI_COLOR_RESET "\n");
    printf(ANSI_BACKGROUND_COLOR_MAGENTA "Lorem ipsum dolor sit amet." ANSI_COLOR_RESET "\n");
    printf(ANSI_BACKGROUND_COLOR_CYAN "Lorem ipsum dolor sit amet." ANSI_COLOR_RESET "\n");
    printf(ANSI_BACKGROUND_COLOR_WHITE "Lorem ipsum dolor sit amet." ANSI_COLOR_RESET "\n");

    return 0;
}