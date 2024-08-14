#include <kernel.h>
#include "display/char_print.h"
#include "idt/idt.h"
#include "io/io.h"
#include <8259_PIC/pic.h>
#include "heap/kernel_heap.h"

extern uint16_t * video_mem;
extern uint8_t terminal_col;
extern uint8_t terminal_row;

static void init_global_vars(void) {
    video_mem = (uint16_t*)VIDEO_MEMORY_ADDRESS;
    terminal_col = 0;
    terminal_row = 0;
}

void kernel_main(void)
{
    init_global_vars();
    vga_init();
    print_str("kernel started\n");

    kheap_init(); // stuck here has no effect kernel_construct_heap_table();

    idt_init();
    pic_setup();
    enable_interrupts();

    void* p1 = kmalloc(50);
    void* p2 = kmalloc(4096*5);
    void* p3 = kmalloc(100);
    kfree(p2);
    void *p4 = kmalloc(100);
    kfree(p4);
    void *p5 = kmalloc(5000); // this to test malloc

    if (p1 || p2 || p3 || p4 || p5) {}

}
