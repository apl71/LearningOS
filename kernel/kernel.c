#include "../drivers/screen.h"

int main() {
    // clear screen and print banner
    clear_screen();
    char message[] = "Welcome to LOS.\n";
    print_string(message, GREEN_ON_BLACK);
}