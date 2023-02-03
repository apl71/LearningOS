#ifndef CONST_H_
#define CONST_H_

// static char ok_msg[] = " [Done]\n";

// static char os_hello_msg[] = "Welcome to my OS.\n";
// static char idt_init_msg[] = "Initializing IDT.\n";
// static char pic_init_msg[] = "Initializing PIC.\n";
// static char exception_msg[]  = "Loading ISRs for exceptions.";
// static char set_idt_33_msg[] = "Loading ISR for interrupt vector 33.";
// static char load_idtr_msg[]  = "Loading IDTR and enabling hardware interrupt.";
// static char pic_remap_msg[]  = "Remapping pic.";
// static char clear_mask_msg[] = "Clearing mask for IRQ 1.";

#define new_line        "\n"

#define ok_msg          "[Done]\n"

#define os_hello_msg    "Welcome to my OS.\n"
#define idt_init_msg    "Initializing IDT.\n"
#define pic_init_msg    "Initializing PIC.\n"
#define exception_msg   "Loading ISRs for exceptions. "
#define set_idt_33_msg  "Loading ISR for interrupt vector 33. "
#define load_idtr_msg   "Loading IDTR and enabling hardware interrupt. "
#define pic_remap_msg   "Remapping pic. "
#define clear_mask_msg  "Clearing mask for IRQ 1. "
#define detect_mem_msg  "Detecting memory.\n"
#define low_mem_msg     "Low memory in KB: "

#endif