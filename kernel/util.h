#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

void memory_copy(char *source, char *dest, int nbyte);

void memory_set(char *mem, char value, int length);

// 计算数字位数
int len_nums(int32_t num, int radix);

#endif