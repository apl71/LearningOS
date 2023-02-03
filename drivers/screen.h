#ifndef SCREEN_H_
#define SCREEN_H_

#include <stdint.h>

#define VIDEO_ADDRESS   (unsigned char *)0xb8000    // 显示存储在主存中映射的地址
#define MAX_ROWS        25                          // 行数
#define MAX_COLS        80                          // 列数

// 定义颜色
#define BLACK           0x00
#define BLUE            0x01
#define GREEN           0x02
#define CYAN            0x03
#define RED             0x04
#define MAGENTA         0x05
#define BROWN           0x06
#define LIGHT_GRAY      0x07
#define DARK_GRAY       0x08
#define LIGHT_BLUE      0x09
#define LIGHT_GREEN     0x0a
#define LIGHT_CYAN      0x0b
#define LIGHT_RED       0x0c
#define LIGHT_MAGENTA   0x0d
#define YELLOW          0x0e
#define WHITE           0x0f

// 定义常用颜色背景组合
#define WHITE_ON_BLACK  (BLACK << 8 | WHITE)
#define GREEN_ON_BLACK  (BLACK << 8 | GREEN)

// 显示设备的IO接口
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

// 显示设备接口函数

// 在指定位置打印字符，默认黑底白字，如果col或row不可用（<0），则在光标处打印
// 打印结束后，光标移动到下一个字符位置
void print_char_at(char character, int col, int row, char attr);

// 在指定位置打印字符串，默认黑底白字
void print_string_at(char message[], int col, int row, char attr);

// 在光标处打印字符串
void print_string(char message[], char attr);

// 用行列号计算出偏移量
int get_screen_offset(int col, int row);

// 从设备寄存器中获取光标的值
int get_cursor();

// 设置设备寄存器中光标的值
void set_cursor(int offset);

// 清除屏幕
void clear_screen();

// 处理屏幕滚动
int handle_scrolling(int cursor_offset);

// 打印整数，不超过32位，最高支持36进制
void print_int(int32_t num, int radix, char attr);

#endif