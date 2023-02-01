#ifndef LOW_LEVEL_H_
#define LOW_LEVEL_H_

// 低级IO接口交互

// 从接口输入一个字节
unsigned char port_byte_in(unsigned short port);

// 向接口输出一个字节
void port_byte_out(unsigned short port, unsigned char data);

// 从接口输入一个字
unsigned short port_word_in(unsigned short port);

// 向接口输出一个字
void port_word_out(unsigned short port, unsigned short data);

// 用于老旧机器上等待PIC重初始化等的简单等待操作
void io_wait();

#endif