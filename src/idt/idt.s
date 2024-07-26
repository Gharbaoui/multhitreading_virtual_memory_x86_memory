section .asm

extern keyboard_handler_21h
extern timer_handler_20h
extern empty_interrupt_handler
global int21h_int
global int20h_int
global idt_load
global enable_interrupts
global empty_interrupt_int

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8] ; the argument of the function 
    lidt [ebx]
    pop ebp
    ret

enable_interrupts:
    sti
    ret

int21h_int:
    cli
    pusha
    call keyboard_handler_21h
    popa
    sti
    iret

int20h_int:
    cli
    pusha
    call timer_handler_20h
    popa
    sti
    iret


empty_interrupt_int:
    cli
    pusha
    call empty_interrupt_handler
    popa
    sti
    iret