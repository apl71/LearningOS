#ifndef CONST_H_
#define CONST_H_

#define MSG_NEWLINE         "\n"
#define MSG_BLANK           " "
#define MSG_HEX_HEADER      "0x"

#define MSG_OK              "[Done]\n"

#define MSG_HELLO_OS        "Welcome to Learning OS.\n"
#define MSG_IDT_INIT        "Initializing IDT.\n"
#define MSG_PIC_INIT        "Initializing PIC.\n"
#define MSG_EXCEPTION       "Loading ISRs for exceptions. "
#define MSG_SET_IDT_33      "Loading ISR for interrupt vector 33. "
#define MSG_LOAD_IDTR       "Loading IDTR and enabling hardware interrupt. "
#define MSG_PIC_REMAP       "Remapping pic. "
#define MSG_CLEAR_MASK      "Clearing mask for IRQ 1. "
#define MSG_MMAP_LENGTH     "MMAP length = "
#define MSG_MMAP_TITLE      "Base Address       Length             Type                          ACPI 3.x\n"
#define MSG_USABLE_MEM      "1: Usable memory              "
#define MSG_RESERVED_MEM    "2: Reserved memory            "
#define MSG_ACPI_RECLAIM    "3: ACPI reclaimable memory    "
#define MSG_ACPI_NVS        "4: ACPI NVS memory            "
#define MSG_BAD_MEM         "5: Area containing bad memory " 
#define MSG_UNKNOWN_MEM     "Unknown memory type                "
#define MSG_MEM_SIZE        "Usable memory size in bytes: "

#endif