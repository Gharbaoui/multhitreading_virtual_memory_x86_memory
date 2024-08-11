#include "kernel_heap.h"

heap_table_t kernel_heap_table;
heap_t kernel_heap;

static void kernel_construct_heap_table()
{
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY*)KERNEL_TABLE_ADDRESS;
    kernel_heap_table.total = KERNEL_HEAP_SIZE_IN_BYTES / KERNEL_BLOCK_SIZE_IN_BYTES;
    memset(kernel_heap_table.entries, 0, kernel_heap_table.total * sizeof(HEAP_BLOCK_TABLE_ENTRY));
}

void kheap_init()
{
    kernel_construct_heap_table();
    int status = heap_create(&kernel_heap_table,
    (void*)KERNEL_HEAP_ADDRESS,
    (void*)(KERNEL_HEAP_ADDRESS + KERNEL_HEAP_SIZE_IN_BYTES),
    &kernel_heap);
    if (status < 0)
    {
        print_str("Failed to create kernel heap\n");
    }
}

void* kmalloc(size_t size)
{
    return heap_malloc(&kernel_heap, size);
}