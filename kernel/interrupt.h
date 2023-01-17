#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <stdint.h>

#define ADDRESS_32              uint32_t        // 表示32位系统内存地址
#define LOW_16(ADDR)            ((uint16_t)(ADDR) & 0xffff)
#define HIGH_16(ADDR)           ((uint16_t)((ADDR) >> 16) & 0xffff)

#define IDT_MAX_DESCRIPTORS     256             // IDT长度

// IDT表项
typedef struct {
    uint16_t isr_low;
    uint16_t kernel_cs;                 // 在调用isr前会将该选择子选择的gdt加载到cs寄存器
    uint8_t  reserved;
    uint8_t  attributes;
    uint16_t isr_high;
} __attribute__((packed)) idt_entry_t;

// 定义GDT
__attribute__((aligned(0x10)))
static idt_entry_t idt[IDT_MAX_DESCRIPTORS];

// idtr结构体
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr_t;

// 定义idtr
static idtr_t idtr;

// 通用异常处理函数
__attribute((noreturn))
void exception_handler(void);

// 写入IDT表项，iv是中断向量，handler表示处理程序地址
void set_idt(int iv, ADDRESS_32 handler);

// 初始化IDT
extern void *isr_stub_table[];
void idt_init();

#endif