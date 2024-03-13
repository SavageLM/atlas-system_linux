BITS 64

    global asm_puts  ; EXPORT function
    extern asm_strlen ; pulls in asm_strlen

    section .text

    ; size_t asm_puts(int c);

asm_puts:
    push rbp
    mov rbp, rsp  ; Setup stack
    push rsi
    push rdx ; store rdi value in stack
    mov rsi, rdi ; moves top of stack into rsi

    call asm_strlen
    mov rdi, 1
    mov rdx, rax ; move rax value into r13
    mov rax, 1
    syscall

    pop rdx
    pop rsi
    pop rbp
    ret ; exit