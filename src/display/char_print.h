#pragma once
#include <stdint.h>

#define VIDEO_MEMORY_ADDRESS 0xb8000 
#define VGA_WIDTH 80
#define VGA_HEIGHT 20

uint16_t char_construct(char c, uint8_t color);
void vga_init(void);
void putchar_at_location(uint8_t x, uint8_t y, char c, uint8_t color);
void writechar_and_move_to_next_place(char c, uint8_t color);
void print_str(const char *str);