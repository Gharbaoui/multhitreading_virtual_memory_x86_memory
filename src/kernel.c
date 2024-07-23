#include <kernel.h>
#include "display/char_print.h"
#include "idt/idt.h"
#include "io/io.h"

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
    const char *msg1 = "Hello, world\n";
    const char *msg2 = "new-message just for test\n";
    init_global_vars();
    vga_init();
    idt_init();

    print_str(msg1);
    print_str(msg2);

    uint8_t value1 = 90;
    uint16_t value2 = 80;

    uint16_t add1 = 23;
    uint16_t add2 = 67;

    outb(add1, value1);
    outw(add2, value2);

}
