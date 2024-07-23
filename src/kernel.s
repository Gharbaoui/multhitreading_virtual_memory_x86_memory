[BITS 32]
global _start
extern kernel_main
CODE_SEGMENT_ENTRY_INDEX equ 0x08
DATA_SEGMENT_ENTRY_INDEX equ 0x10

_start:
  mov ax, DATA_SEGMENT_ENTRY_INDEX ; data segment of gdt entry 0 gdt_data 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  mov ebp,  0x00200000
  mov esp, ebp

  in al, 0x92
  or al, 2
  out 0x92, al

  call kernel_main
  call test
  hlt
  jmp $

test:
  ret

times 512-($-$$) db 0