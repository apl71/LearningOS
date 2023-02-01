#include "../drivers/screen.h"
#include "interrupt.h"

int main() {
    // clear screen and print banner
    clear_screen();
    char hello[] = "Welcome to LOS.\n";
    print_string(hello, GREEN_ON_BLACK);
    char int_message[] = "Initializing interrupt.\n";
    print_string(int_message, GREEN_ON_BLACK);
    idt_init();
}