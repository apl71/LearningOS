#include "screen.h"
#include "../kernel/low_level.h"

void print_char_at(char character, int col, int row, char attr) {
    // 获取显示设备映射主存的首地址
    unsigned char *vidmem = VIDEO_ADDRESS;
    // 计算坐标偏移量
    int offset = get_screen_offset(col, row);
    // 默认属性是白底黑字
    if (!attr) {
        attr = WHITE_ON_BLACK;
    }
    // 填充数据
    vidmem[offset++] = character;
    vidmem[offset++] = attr;
}

void print_string_at(char *message, int col, int row, char attr) {
    int count = 0;
    while (message[count] != 0x00) {
        print_char_at(message[count], col, row, attr);
        count++;
        col++;
        if (col >= MAX_COLS) {
            col = 0;
            row++;
        }
    }
}

int get_screen_offset(int col, int row) {
    return (row * MAX_COLS + col) * 2;
}

int get_cursor() {
    // 寄存器14是光标偏移的高字节
    // 寄存器15是光标偏移的低字节
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen() {
    int col, row;
    for (col = 0; col < MAX_COLS; ++col) {
        for (row = 0; row < MAX_ROWS; ++row) {
            print_char_at(' ', col, row, 0);
        }
    }
}