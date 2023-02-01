#include "interrupt.h"
#include "pic.h"
#include "../drivers/screen.h"
#include "low_level.h"

void set_idt(int iv, ADDRESS_32 handler, uint8_t flag) {
    if (iv >= 255 || iv <= 0) {
        return;
    }
    idt[iv].isr_low    = LOW_16(handler);
    idt[iv].kernel_cs  = 0x08;                  // 代码段选择子
    idt[iv].reserved   = 0;
    idt[iv].attributes = flag;                  // P=1 DPL=00 0=0 D=1 Type=110
    idt[iv].isr_high   = HIGH_16(handler);
}

void idt_init() {
    // 重映射PIC
    print_string(pic_remap_msg, GREEN_ON_BLACK);
    PIC_remap(0x20, 0x28);

    // 初始化IDTR
    idtr.base  = (ADDRESS_32)idt;
    idtr.limit = IDT_MAX_DESCRIPTORS * sizeof(idt_entry_t) - 1;

    // 初始化异常部分
    print_string(exception_msg, GREEN_ON_BLACK);
    for (uint8_t vector = 0; vector < 32; ++vector) {
        set_idt(vector, (ADDRESS_32)isr_stub_table[vector], INTERRUPT_GATE);
    }

    print_string(set_idt_33_msg, GREEN_ON_BLACK);
    set_idt(0x21, (ADDRESS_32)interrupt_handler, INTERRUPT_GATE);

    // 重置PIC掩码
    print_string(clear_mask_msg, GREEN_ON_BLACK);
    IRQ_clear_mask(1);

    // 加载idtr
    print_string(load_idtr_msg, GREEN_ON_BLACK);
    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");   // 启动中断
}

void interrupt_handler() {
    char message[] = "interrupt_handler() called.\n";
    print_string(message, WHITE_ON_BLACK);

    uint8_t scancode = port_byte_in(0x60);

    PIC_send_EOI(1);
}

void exception_handler() {
    __asm__ volatile ("cli; hlt");
}