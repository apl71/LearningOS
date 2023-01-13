#include "../drivers/screen.h"

void main() {
    // 清除屏幕，然后打印欢迎语句
    // clear_screen();
    // print_char_at('W', 0, 0, GREEN_ON_BLACK);
    // print_char_at('e', 1, 0, GREEN_ON_BLACK);
    // print_char_at('l', 2, 0, GREEN_ON_BLACK);
    // print_char_at('c', 3, 0, GREEN_ON_BLACK);
    // print_char_at('o', 4, 0, GREEN_ON_BLACK);
    // print_char_at('m', 5, 0, GREEN_ON_BLACK);
    // print_char_at('e', 6, 0, GREEN_ON_BLACK);
    // print_char_at(' ', 7, 0, GREEN_ON_BLACK);
    // print_char_at('t', 8, 0, GREEN_ON_BLACK);
    // print_char_at('o', 9, 0, GREEN_ON_BLACK);
    // print_char_at(' ', 10, 0, GREEN_ON_BLACK);
    // print_char_at('m', 11, 0, GREEN_ON_BLACK);
    // print_char_at('y', 12, 0, GREEN_ON_BLACK);
    // print_char_at(' ', 13, 0, GREEN_ON_BLACK);
    // print_char_at('O', 14, 0, GREEN_ON_BLACK);
    // print_char_at('S', 15, 0, GREEN_ON_BLACK);
    char message[] = "We";
    print_string_at(message, 0, 0, GREEN_ON_BLACK);
}