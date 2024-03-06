extern io_get_dec, io_print_dec, get_udec, io_get_dec
extern io_get_char, io_print_char
extern io_newline
global main

section .bss
    x1 resw 1
    x2 resw 1
    x3 resw 1
    y1 resw 1
    y2 resw 1
    y3 resw 1
    s1 resw 1
    s2 resw 1
    r1 resw 1
    r2 resw 1
    r3 resw 1
    r4 resw 1
    
section .text
main:
    call io_get_dec
    mov word[x1], ax
    call io_get_dec
    mov word[y1], ax
    call io_get_dec
    mov word[x2], ax
    call io_get_dec
    mov word[y2], ax   
    call io_get_dec
    mov word[x3], ax
    call io_get_dec
    mov word[y3], ax
    
    mov ax, word[x2]
    sub ax, word[x1]
    mov word[r1], ax
    
    mov ax, word[y3]
    sub ax, word[y1]
    mov word[r2], ax
    
    mov ax, word[x3]
    sub ax, word[x1]
    mov word[r3], ax
    
    mov ax, word[y2]
    sub ax, word[y1]
    mov word[r4], ax
    
    mov ax, word[r1]
    imul word[r2]
    ; dx:ax -> ebx
    movzx ebx, dx
    shl ebx, 16
    mov bx, ax    
    
    mov ax, word[r3]
    imul word[r4]
    ; dx:ax -> ecx
    movzx ecx, dx
    shl ecx, 16
    mov cx, ax  
    
    mov eax, ebx 
    sub eax, ecx
    ; abs (eax)
    mov ecx, eax
    sar ecx, 31
    xor eax, ecx
    sub eax, ecx
    
    mov bx, 2 
    div bx
    
    mov word[s1], ax
    mov word[s2], dx
    xor eax, eax
    mov ax, word[s1]
    
    call io_print_dec; вывод eax
    mov bx, 46
    mov ax, bx
    call io_print_char; вывод точки
    xor eax, eax
    mov ax, word[s2]
    mov bl, 5
    mul bl
    ;mov eax, edx
    call io_print_dec; вывод остатка
    xor eax, eax
    ret