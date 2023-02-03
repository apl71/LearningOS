#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

void memory_copy(char *source, char *dest, int nbyte);

void memory_set(char *mem, char value, int length);

// 计算数字位数，radix表示进制，结果不计算符号占位，仅计算数码占位
int len_nums(int32_t num, int radix);

#endif