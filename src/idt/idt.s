section .asm

global idt_load

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8] ; the argument of the function 
    lidt [ebx]
    pop ebp
    ret