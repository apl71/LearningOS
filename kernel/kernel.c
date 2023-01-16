#include "../drivers/screen.h"

int main() {
    // clear screen and print banner
    clear_screen();
    print_char_at('W',  0, 0, GREEN_ON_BLACK);
    print_char_at('e',  1, 0, GREEN_ON_BLACK);
    print_char_at('l',  2, 0, GREEN_ON_BLACK);
    print_char_at('c',  3, 0, GREEN_ON_BLACK);
    print_char_at('o',  4, 0, GREEN_ON_BLACK);
    print_char_at('m',  5, 0, GREEN_ON_BLACK);
    print_char_at('e',  6, 0, GREEN_ON_BLACK);
    print_char_at(' ',  7, 0, GREEN_ON_BLACK);
    print_char_at('t',  8, 0, GREEN_ON_BLACK);
    print_char_at('o',  9, 0, GREEN_ON_BLACK);
    print_char_at(' ', 10, 0, GREEN_ON_BLACK);
    print_char_at('O', 11, 0, GREEN_ON_BLACK);
    print_char_at('S', 12, 0, GREEN_ON_BLACK);
    print_char_at('.', 13, 0, GREEN_ON_BLACK);
    print_char_at('\0',14, 0, GREEN_ON_BLACK);
    int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    char message[] = "Welcome to OS.\0";
    // print_string_at(message, 0, 0, GREEN_ON_BLACK);
}