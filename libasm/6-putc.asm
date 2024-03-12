BITS 64

    global asm_putc  ; EXPORT function

    section .text

    ; size_t asm_putc(int c);

asm_putc:
    push rbp
    mov rbp, rsp  ; Setup stack
    push rdi ; store rdi value in stack

    mov rax, 1 ; move value of 1 into rax
    mov rdi, 1 ;
    mov rsi, rsp
    mov rdx, 1
    syscall

    pop rdi
    pop rbp
    ret ; exit