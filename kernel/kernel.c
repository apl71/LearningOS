#include "../drivers/screen.h"

int main() {
    // clear screen and print banner
    clear_screen();
    int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    char message[] = "Welcome to OS.\0";
    print_string_at(message, 0, 0, GREEN_ON_BLACK);
}