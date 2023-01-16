#include "screen.h"
#include "../kernel/low_level.h"
#include "../kernel/util.h"

void print_char_at(char character, int col, int row, char attr) {
    // 获取显示设备映射主存的首地址
    unsigned char *vidmem = VIDEO_ADDRESS;
    // 默认属性是白底黑字
    if (!attr) {
        attr = WHITE_ON_BLACK;
    }
    int offset = 0;
    if (col < 0 || row < 0) {
        // 获取光标位置
        offset = get_cursor();
    } else {
        // 计算内存偏移量
        offset = get_screen_offset(col, row);
    }
    // 处理回车
    if (character == '\n') {
        int rows = offset / (2 * MAX_COLS);
        offset = get_screen_offset(0, rows + 1);
    } else {
        // 填充数据
        vidmem[offset++] = character;
        vidmem[offset++] = attr;
    }
    // 处理滚动屏幕
    offset = handle_scrolling(offset);
    // 设定光标位置
    set_cursor(offset);
}

void print_string_at(char message[], int col, int row, char attr) {
    if (col < 0 || row < 0) {
        int offset = get_cursor();
        row = offset / (2 * MAX_COLS);
        col = (offset / 2) % MAX_COLS;
    }
    int count = 0;
    while (message[count] != 0x00) {
        print_char_at(message[count], col++, row, attr);
        if (col >= MAX_COLS || message[count] == '\n') {
            col = 0;
            row++;
        }
        count++;
    }
}

void print_string(char message[], char attr) {
    print_string_at(message, -1, -1, attr);
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
    set_cursor(get_screen_offset(0, 0));
}

int handle_scrolling(int cursor_offset) {
    // 没有超出屏幕，无需处理
    if (cursor_offset < MAX_COLS * MAX_ROWS * 2) {
        return cursor_offset;
    }
    // 每行后退一行
    int row;
    for (row = 1; row < MAX_ROWS; ++row) {
        memory_copy(get_screen_offset(0, row) + VIDEO_ADDRESS,
                    get_screen_offset(0, row - 1) + VIDEO_ADDRESS,
                    2 * MAX_COLS);
    }
    // 最后一行清零
    char *last_line = get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
    int i;
    for (i = 0; i < MAX_COLS * 2; ++i) {
        last_line[i] = 0;
    }
    // 偏移回退一行
    cursor_offset = get_screen_offset(0, MAX_ROWS - 1);
    return cursor_offset;
}