#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <stdint.h>

#define ADDRESS_32              uint32_t        // 表示32位系统内存地址
#define LOW_16(ADDR)            ((uint16_t)(ADDR) & 0xffff)
#define HIGH_16(ADDR)           ((uint16_t)((ADDR) >> 16) & 0xffff)

#define IDT_MAX_DESCRIPTORS     256             // IDT长度

// flags
#define INTERRUPT_GATE          0x8e
#define TRAP_GATE               0x8f
#define TASK_GATE               0x85

// 提示信息
static const char pic_remap_msg[]  = "Remapping pic.\n";
static const char exception_msg[]  = "Loading ISRs for exceptions.\n";
static const char set_idt_33_msg[] = "Loading ISR for interrupt vector 33.\n";
static const char clear_mask_msg[] = "Clearing mask for IRQ 1.\n";
static const char load_idtr_msg[]  = "Loading IDTR.\n";

// IDT表项
typedef struct {
    uint16_t isr_low;
    uint16_t kernel_cs;                 // 在调用isr前会将该选择子选择的gdt加载到cs寄存器
    uint8_t  reserved;
    uint8_t  attributes;
    uint16_t isr_high;
} __attribute__((packed)) idt_entry_t;

// 定义IDT
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
__attribute__((noreturn))
void exception_handler();

// 写入IDT表项，iv是中断向量，handler表示处理程序地址
void set_idt(int iv, ADDRESS_32 handler, uint8_t);

// isr表项，isr[iv]表示中断向量iv要用到的isr地址
extern void *isr_stub_table[];
// 初始化IDT
void idt_init();

extern void interrupt_handler();

#endif