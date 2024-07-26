#include "pic.h"
#include <io/io.h>

void pic_setup(void)
{
    // setting PICs for initialisation 
    outb(PIC_MASTER_CMD_PORT, START_INIT_CMD);
    outb(PIC_SLAVE_CMD_PORT, START_INIT_CMD);
    
    // let's set vector offset
    // for master
    outb(PIC_MASTER_DATA_PORT, MASTER_VECTOR_OFFSET);
    // for slave
    outb(PIC_SLAVE_DATA_PORT, SLAVE_VECTOR_OFFSET);

    // connection between master and slave
    outb(PIC_MASTER_DATA_PORT, 4);
    // 4 = 100 it says that slave is connected to master via IRQ2 so why not 2, becuase it
    // uses bit 2 instead of the value 2 and when we set bit 2 as you see `4=bit[2]=1,bit[1]=0,bit[0]=0`
    outb(PIC_SLAVE_DATA_PORT, 2);


    // mode setup since pic can work with multiple architecture it supports them
    // and we need to configure them
    outb(PIC_MASTER_DATA_PORT, ICW_MODE_8086);
    outb(PIC_SLAVE_DATA_PORT, ICW_MODE_8086);

    // since I don't know what is masked and what is not I'll enable all of them now
    outb(PIC_MASTER_DATA_PORT, 0x0);
    outb(PIC_SLAVE_DATA_PORT, 0x0);
}

void pic_send_eoi(uint8_t irq)
{
    irq -= MASTER_VECTOR_OFFSET;
    outb(PIC_MASTER_CMD_PORT, PIC_EOI);
    if (irq >= 8) {
        outb(PIC_SLAVE_CMD_PORT, PIC_EOI);
    }
}