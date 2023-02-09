#ifndef CONST_H_
#define CONST_H_

#define new_line            "\n"

#define ok_msg              "[Done]\n"

#define os_hello_msg        "Welcome to my OS.\n"
#define idt_init_msg        "Initializing IDT.\n"
#define pic_init_msg        "Initializing PIC.\n"
#define exception_msg       "Loading ISRs for exceptions. "
#define set_idt_33_msg      "Loading ISR for interrupt vector 33. "
#define load_idtr_msg       "Loading IDTR and enabling hardware interrupt. "
#define pic_remap_msg       "Remapping pic. "
#define clear_mask_msg      "Clearing mask for IRQ 1. "
#define mmap_length_msg     "MMAP length = "

#endif