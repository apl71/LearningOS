#ifndef CONST_H_
#define CONST_H_

#define new_line            "\n"
#define blank               " "
#define hex_head            "0x"

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
#define mmap_title_msg      "Base Address       Length             Type                          ACPI 3.x\n"
#define usable_mem_msg      "1: Usable memory              "
#define reserved_mem_msg    "2: Reserved memory            "
#define acpi_reclaim_msg    "3: ACPI reclaimable memory    "
#define acpi_nvs_msg        "4: ACPI NVS memory            "
#define bad_mem_msg         "5: Area containing bad memory " 
#define unknown_mem_msg     "Unknown memory type                "
#define mem_size_msg        "Usable memory size in bytes: "

#endif