#ifndef SCREEN_H_
#define SCREEN_H_

#define VIDEO_ADDRESS   (unsigned char *)0xb8000    // 显示存储在主存中映射的地址
#define MAX_ROWS        25                          // 行数
#define MAX_COLS        80                          // 列数

#define WHITE_ON_BLACK  0x0f                        // 定义颜色和背景
#define GREEN_ON_BLACK  0x02

// 显示设备的IO接口
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

// 显示设备接口函数

// 在指定位置打印字符，默认黑底白字
void print_char_at(char character, int col, int row, char attr);

// 在指定位置打印字符串，默认黑底白字
void print_string_at(char *message, int col, int row, char attr);

// 用行列号计算出偏移量
int get_screen_offset(int col, int row);

// 从设备寄存器中获取光标的值
int get_cursor();

// 设置设备寄存器中光标的值
void set_cursor(int offset);

// 清除屏幕
void clear_screen();

#endif