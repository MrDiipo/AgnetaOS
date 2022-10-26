
#ifndef AGNETAOS_IDT_H
#define AGNETAOS_IDT_H

#include <stdint.h>

void idt_init();

struct idt_desc {
    uint16_t offset_1; // Offset bits 0 - 15
    uint16_t selector;  // Selector that is in our GDT
    uint_8_t zero; // Does nothing. unused set to zero
    uint8_t type_attr; // Descriptor type and attributes
    uint16_t offset_2; // Offset bits 16 - 31
} __attribute__((packed));

struct idtr_desc {
    uint16_t limit; // Size of  descriptor table -1
    uint32_t base; // Base address of the start of the interrupt descriptor table
} __attribute__((packed)) ;

#endif //AGNETAOS_IDT_H
