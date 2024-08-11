#pragma once

#include <stdint.h>
#include <stddef.h>
#include "config.h"
#include "status.h"

#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x1
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x0

#define HEAP_BLOCK_HAS_NEXT 0b10000000
#define HEAP_BLOCK_IS_FIRST 0b01000000

#define GET_ENTRY_TYPE(type) type & 0xf

typedef uint8_t HEAP_BLOCK_TABLE_ENTRY;

typedef struct heap_table_s
{
    HEAP_BLOCK_TABLE_ENTRY *entries;
    size_t total;
} heap_table_t;

typedef struct heap_s {
    heap_table_t* table;
    void* memory_start_address;
} heap_t;

int heap_create(heap_table_t* heap_table, void* saddr, void* end, heap_t* heap);
static void mark_entries_taken(heap_table_t* table, int start_index, int number_of_entries);
void* heap_malloc(heap_t *heap, size_t size);