section .asm
global inb
global inw
global outb
global outw

inb:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov dx, [ebp+0x8]
    in al, dx ; since ax is part of eax this is the return value

    pop ebp
    ret

inw:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov dx, [ebp+0x8]
    in ax, dx ; since ax is part of eax this is the return value

    pop ebp
    ret


outb:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov dx, [ebp+0x8] ; port
    mov al, [ebp+0xc] ; value 8 bit
    out dx, al

    pop ebp
    ret

outw:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov dx, [ebp+0x8] ; port
    mov ax, [ebp+0xc] ; value 16 bit
    out dx, ax

    pop ebp
    ret