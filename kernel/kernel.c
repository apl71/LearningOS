#include "../drivers/screen.h"

void main() {
    // 清除屏幕，然后打印欢迎语句
    clear_screen();
    char message[] = "Welcome to LOS.";
    print_string_at(message, 0, 0, GREEN_ON_BLACK);
}