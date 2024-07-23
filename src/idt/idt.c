#include "idt.h"
#include "config.h"
#include "memory/memory.h"
#include  "display/char_print.h"


interrupt_descriptor interrupt_descriptor_table [INTERRUPT_DESCRIPTOR_TABLE_SIZE];
interrupt_descriptor_table_register idtr;

void idt_zero() {
    print_str("Divide by zero error\n");
}

void set_interrupt_descriptor(uint16_t idt_number, void *function_address)
{
    // offset is the most important now BTW it's just where the function to be executed
    // function pointer
    interrupt_descriptor_table[idt_number].offset_low =
    (uint32_t)(function_address) & 0x0000ffff;
    interrupt_descriptor_table[idt_number].offset_high =
    ((uint32_t)(function_address) & 0xffff0000) >> 16;

    interrupt_descriptor_table[idt_number].segment_selector = KERNEL_CODE_SELECTOR;
    interrupt_descriptor_table[idt_number].reserved = 0;
    interrupt_descriptor_table[idt_number].type_attribute =
    0xEE; // prsent dpl = 3 gate type is interrupt gate
}

void idt_init(void)
{
    memset(interrupt_descriptor_table, 0, sizeof(interrupt_descriptor_table));
    idtr.limit = sizeof(interrupt_descriptor_table) - 1;
    idtr.base_address = (uint32_t)interrupt_descriptor_table;

    set_interrupt_descriptor(0, idt_zero);
    // we are passing &idtr, because lidt takes pointer the structure that holds limit and base
    // and not the value
    idt_load(&idtr);
}