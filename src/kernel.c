#include <kernel.h>
#include "display/char_print.h"
#include "idt/idt.h"
#include "io/io.h"
#include <8259_PIC/pic.h>

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
    const char *msg1 = "Hello, world\n";
    vga_init();
    print_str(msg1);
    idt_init();
    pic_setup();
    enable_interrupts();

}
