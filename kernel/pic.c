#include "pic.h"
#include "low_level.h"

void PIC_send_EOI(IRQ irq) {
    // 由从PIC发送的中断号，需要通知主从两个PIC
    // 由主PIC发送的中断号，只需要通知主PIC
    if (irq >= 8)
        port_byte_out(PIC2_COMMAND, PIC_EOI);
    port_byte_out(PIC1_COMMAND, PIC_EOI);
}

void PIC_remap(int offset1, int offset2) {
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

void IRQ_set_mask(IRQ irq) {
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

void IRQ_clear_mask(IRQ irq) {
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

IRQ PIC_get_irq_reg(uint8_t ocw3) {
    port_byte_out(PIC1_COMMAND, ocw3);
    port_byte_out(PIC2_COMMAND, ocw3);
    return ((IRQ)port_byte_in(PIC2_COMMAND) << 8) | port_byte_in(PIC1_COMMAND);
}

IRQ PIC_get_irr() {
    return PIC_get_irq_reg(PIC_READ_IRR);
}

IRQ PIC_get_isr() {
    return PIC_get_irq_reg(PIC_READ_ISR);
}