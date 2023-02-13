#include "pic.h"
#include "low_level.h"
#include "../drivers/screen.h"
#include "const.h"

void pic_send_eoi(IRQ irq) {
    // 由从PIC发送的中断号，需要通知主从两个PIC
    // 由主PIC发送的中断号，只需要通知主PIC
    if (irq >= 8)
        port_byte_out(PIC2_COMMAND, PIC_EOI);
    port_byte_out(PIC1_COMMAND, PIC_EOI);
}

void pic_remap(int offset1, int offset2) {
    // 保存掩码mask？
    unsigned char mask1 = port_byte_in(PIC1_DATA);
    unsigned char mask2 = port_byte_in(PIC2_DATA);

    // 初始化为层叠模式
    port_byte_out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    port_byte_out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    // 设置向量偏移
    port_byte_out(PIC1_DATA, offset1);
    io_wait();
    port_byte_out(PIC2_DATA, offset2);
    io_wait();
    // 将主PIC的IRQ 2连接到从PIC
    port_byte_out(PIC1_DATA, 4);     // 4 = b0000 0100
    io_wait();
    port_byte_out(PIC2_DATA, 2);     // 2 = b0000 0010
    io_wait();

    port_byte_out(PIC1_DATA, ICW4_8086);
    io_wait();
    port_byte_out(PIC2_DATA, ICW4_8086);
    io_wait();

    // 恢复掩码mask
    port_byte_out(PIC1_DATA, mask1);
    port_byte_out(PIC2_DATA, mask2);
}

void irq_set_mask(IRQ irq) {
    // PIC的数据端口
    uint16_t port;
    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    // 在IMR原始值的基础上设置第irq位为1
    uint8_t value = port_byte_in(port) | (1 << irq);
    port_byte_out(port, value);
}

void irq_set_all_mask() {
    port_byte_out(PIC1_DATA, 0xff);
    port_byte_out(PIC2_DATA, 0xff);
}

void irq_clear_mask(IRQ irq) {
    // PIC的数据端口
    uint16_t port;
    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    // 在IMR原始值的基础上设置第irq位为1
    uint8_t value = port_byte_in(port) & ~(1 << irq);
    port_byte_out(port, value);
}

void irq_clear_all_mask() {
    port_byte_out(PIC1_DATA, 0x00);
    port_byte_out(PIC2_DATA, 0x00);
}

IRQ pic_get_irq_reg(uint8_t ocw3) {
    port_byte_out(PIC1_COMMAND, ocw3);
    port_byte_out(PIC2_COMMAND, ocw3);
    return ((IRQ)port_byte_in(PIC2_COMMAND) << 8) | port_byte_in(PIC1_COMMAND);
}

IRQ pic_get_irr() {
    return pic_get_irq_reg(PIC_READ_IRR);
}

IRQ pic_get_isr() {
    return pic_get_irq_reg(PIC_READ_ISR);
}

void pic_init() {
    // 关闭PIC
    irq_set_all_mask();

    // 重映射PIC
    print_string(MSG_PIC_REMAP, WHITE_ON_BLACK);
    pic_remap(PIC1_VECTOR_OFFSET, PIC2_VECTOR_OFFSET);
    print_string(MSG_OK, GREEN_ON_BLACK);

    // 重置PIC掩码
    print_string(MSG_CLEAR_MASK, WHITE_ON_BLACK);
    irq_set_all_mask();
    irq_clear_mask(1);
    print_string(MSG_OK, GREEN_ON_BLACK);
}