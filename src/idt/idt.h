#pragma once
#include <stdint.h>

struct interrupt_descriptor_s
{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t reserved;
    uint8_t type_attribute;
    uint16_t offset_high;
} __attribute__((packed));


struct interrupt_descriptor_table_register_s {
    uint16_t limit;
    uint32_t base_address;
}  __attribute__((packed));

typedef struct interrupt_descriptor_s interrupt_descriptor;
typedef struct interrupt_descriptor_table_register_s interrupt_descriptor_table_register;

extern void idt_load(interrupt_descriptor_table_register*);

void set_interrupt_descriptor(uint16_t idt_number, void *function_address);
void idt_zero();
void idt_init(void);
extern void enable_interrupts();