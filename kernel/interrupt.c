#include "interrupt.h"

void set_idt(int iv, ADDRESS_32 handler) {
    if (iv >= 255 || iv <= 0) {
        return;
    }
    idt[iv].isr_low    = LOW_16(handler);
    idt[iv].kernel_cs  = 0x08;                  // 代码段选择子
    idt[iv].reserved   = 0;
    idt[iv].attributes = 0x8e;                  // P=1 DPL=00 0=0 D=1 Type=110
    idt[iv].isr_high   = HIGH_16(handler);
}

void idt_init() {
    idtr.base  = (ADDRESS_32)idt;
    idtr.limit = IDT_MAX_DESCRIPTORS * sizeof(idt_entry_t) - 1;

    // 初始化异常部分
    for (uint8_t vector = 0; vector < 32; ++vector) {
        set_idt(vector, (ADDRESS_32)isr_stub_table[vector]);
    }

    // 加载idtr
    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");   // 启动中断
}

void exception_handler() {
    __asm__ volatile ("cli; hlt");
}