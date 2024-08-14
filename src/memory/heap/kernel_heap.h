#pragma once
#include "heap.h"
#include "memory/memory.h"
#include "display/char_print.h"

void kheap_init();
void* kmalloc(size_t size);
void kfree(void* ptr);