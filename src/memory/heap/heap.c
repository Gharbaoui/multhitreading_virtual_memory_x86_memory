#include "heap.h"
#include <stdbool.h>

static bool alignment_check(void* addr)
{
    return ((unsigned int)(addr) % KERNEL_BLOCK_SIZE_IN_BYTES) == 0;
}

int heap_create(heap_table_t* heap_table, void* saddr, void* end, heap_t* heap)
{
    // simple check of the provided heap_table
    if (alignment_check(saddr) && alignment_check(end))
    {
        // size check
        if ((unsigned int)(end - saddr) / KERNEL_BLOCK_SIZE_IN_BYTES == heap_table->total)
        {
            heap->memory_start_address = saddr;
            heap->table = heap_table;
            return 0;
        }
    }
    return -EINVARG;
}

static int blocks_required_to_satisfy_size(size_t size)
{
    if (size % KERNEL_BLOCK_SIZE_IN_BYTES == 0)
    {
        return size / KERNEL_BLOCK_SIZE_IN_BYTES;
    }
    // int num_of_bytes = ((size - (size % KERNEL_BLOCK_SIZE_IN_BYTES)) + KERNEL_BLOCK_SIZE_IN_BYTES);
    return ((size - (size % KERNEL_BLOCK_SIZE_IN_BYTES)) + KERNEL_BLOCK_SIZE_IN_BYTES) / KERNEL_BLOCK_SIZE_IN_BYTES;
}

void* heap_malloc(heap_t *heap, size_t size)
{
    int i, j, number_of_entries;
    heap_table_t* table;

    number_of_entries = blocks_required_to_satisfy_size(size);
    table = heap->table;
    i = 0;

    while (i < table->total)
    {
        j = i;
        while ((j - i) < number_of_entries)
        {
            if ((GET_ENTRY_TYPE(table->entries[j])) != HEAP_BLOCK_TABLE_ENTRY_FREE)
            {
                break;
            }
            ++j;
        }
        if ((j - i) == number_of_entries) // (j - i) how many entries were free
        {
            // we know that we have found our target
            // mark them to be taken
            // return the start address
            mark_entries_taken(table, i, number_of_entries);
            return heap->memory_start_address + (i * KERNEL_BLOCK_SIZE_IN_BYTES);
        }
        ++i;
    }
    return 0x0;
}

static void mark_entries_taken(heap_table_t* table, int start_index, int number_of_entries)
{
    table->entries[start_index] = 0; // reset
    table->entries[start_index] = (HEAP_BLOCK_IS_FIRST | HEAP_BLOCK_TABLE_ENTRY_TAKEN);
    if (number_of_entries > 1)
        table->entries[start_index] |= HEAP_BLOCK_HAS_NEXT;

    int i = 1; // 1 because one entry is already filled
    while (i < number_of_entries)
    {
        table->entries[i + start_index] = HEAP_BLOCK_TABLE_ENTRY_TAKEN;
        if (i + 1 < number_of_entries) // if not last entry
            table->entries[i + start_index] |= HEAP_BLOCK_HAS_NEXT;
        ++i;
    }
}