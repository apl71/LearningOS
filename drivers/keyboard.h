#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <stdint.h>

#define SCANCODE uint8_t

// 将键盘的按键情况打印出来
void print_scancode(SCANCODE scancode);

// 将scan code转换为ascii字符
char scancode_to_char(SCANCODE scancode);

#endif