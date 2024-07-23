#include "char_print.h"

uint16_t * video_mem;
uint8_t terminal_col;
uint8_t terminal_row;

uint16_t char_construct(char c, uint8_t color)
{
    uint16_t res;
    res = color << 8; // set color
    res = res | c; // add char
    return res;
}

void vga_init(void)
{
    for (uint8_t y = 0; y < VGA_HEIGHT; ++y) {
        for (uint8_t x = 0; x < VGA_WIDTH; ++x) {
            putchar_at_location(x, y, 0, 0);
        }
    }
}

void putchar_at_location(uint8_t x, uint8_t y, char c, uint8_t color)
{
    video_mem[y * VGA_WIDTH + x] = char_construct(c, color);
}

void writechar_and_move_to_next_place(char c, uint8_t color) {
    if (c != '\n') {
        putchar_at_location(terminal_col, terminal_row, c, color);
        ++terminal_col;
        if (terminal_col >= VGA_WIDTH) {
            terminal_col = 0;
            terminal_row += 1;
        }
    } else {
        terminal_col = 0;
        terminal_row += 1;
    }

    // if terminal_row >= VGA_HEIGHT MAYBE RESET AND PRINT SOME MESSAGE LATER
}

void print_str(const char *str) {
    uint8_t index = 0;

    while (str[index] != 0) {
        writechar_and_move_to_next_place(str[index], 15);
        ++index;
    }
}
