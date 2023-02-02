#ifndef PIC_H_
#define PIC_H_

#include <stdint.h>

// 定义PIC接口和控制代码
#define PIC1_BASE       0x20
#define PIC2_BASE       0xa0
#define PIC1_COMMAND    PIC1_BASE
#define PIC1_DATA       (PIC1_BASE + 1)
#define PIC2_COMMAND    PIC2_BASE
#define PIC2_DATA       (PIC2_BASE + 1)

#define PIC_EOI         0x20    // 控制代码：中断结束

// 定义ICW
#define ICW1_ICW4       0x01    // ICW4是否启用
#define ICW1_SINGLE     0x02    // 单个或两个层叠式PIC
#define ICW1_INTERVAL4  0x04    // 调用地址间隔4或8（？）
#define ICW1_LEVEL      0x08    // 层级触发模式或边缘模式（？）
#define ICW1_INIT       0x10    // 初始化

#define ICW4_8086       0x01    // 8086/88模式或MCS-80/85模式（？）
#define ICW4_AUTO       0x02    // 自动EOI或普通EOI
#define ICW4_BUF_SLAVE  0x08    // 从PIC缓冲模式（？）
#define ICW4_BUF_MASTER 0x0c    // 主PIC缓冲模式（？）
#define ICW4_SFNM       0x10    // Special fully nested ?

#define PIC_READ_IRR    0x0a    // 读取IRR的指令字
#define PIC_READ_ISR    0x0b    // 读取ISR的指令字

// 定义IRQ编号类型
#define IRQ unsigned char

// 向PIC发送结束中断控制信号
void pic_send_eoi(IRQ irq);

// 重新初始化保护模式下的PIC，参数分别为主从PIC的偏移量
void pic_remap(int offset1, int offset2);

// 设置IMR
void irq_set_mask(IRQ irq);
// 将所有位置为1
void irq_set_all_mask();

// 复位IMR
void irq_clear_mask(IRQ irq);
// 将所有位复位
void irq_clear_all_mask();

// 读取PIC内部寄存器的值
IRQ pic_get_irq_reg(uint8_t ocw3);

// 读取IRR
IRQ pic_get_irr();

// 读取ISR
IRQ pic_get_isr();

// 初始化PIC
void pic_init();

#endif