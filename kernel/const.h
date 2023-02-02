#ifndef CONST_H_
#define CONST_H_

static char ok_msg[] = " [Done]\n";

static char os_hello_msg[] = "Welcome to my OS.\n";
static char idt_init_msg[] = "Initializing IDT.\n";
static char pic_init_msg[] = "Initializing PIC.\n";
static char exception_msg[]  = "Loading ISRs for exceptions.";
static char set_idt_33_msg[] = "Loading ISR for interrupt vector 33.";
static char load_idtr_msg[]  = "Loading IDTR and enabling hardware interrupt.";
static char pic_remap_msg[]  = "Remapping pic.";
static char clear_mask_msg[] = "Clearing mask for IRQ 1.";

#endif