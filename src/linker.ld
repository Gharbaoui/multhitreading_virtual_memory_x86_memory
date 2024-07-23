ENTRY(_start)
OUTPUT_FORMAT(binary)

SECTIONS
{
    /*make sure you load the right componet at
    this location so addressing is correct*/
    . = 1M;
    /* I belive that it should .text : ALIGN(4096) but let's follow for now*/
    .text : ALIGN(4096)
    {
        *(.text)
    }
    .rodata : ALIGN(4096)
    {
        *(.rodata)
    }
    .data : ALIGN(4096)
    {
        *(.data)
    }
    .bss : ALIGN(4096)
    {
        *(.COMMON)
        *(.bss)
    }

    .asm : ALIGN(4096)
    {
        *(.asm)
    }
}