#pragma once
#include <stdint.h>

#define PIC_MASTER_CMD_PORT 0x20
#define PIC_SLAVE_CMD_PORT 0xA0
#define PIC_MASTER_DATA_PORT 0x21
#define PIC_SLAVE_DATA_PORT 0xA1

#define START_INIT_CMD 0x11
#define MASTER_VECTOR_OFFSET 0x20
#define SLAVE_VECTOR_OFFSET (MASTER_VECTOR_OFFSET + 8)

#define PIC_EOI 0x20
#define ICW_MODE_8086 0x1

void pic_setup(void);
void pic_send_eoi(uint8_t irq);