BITS 64

    global asm_puts  ; EXPORT function
    extern asm_strlen ; pulls in asm_strlen

    section .text

    ; size_t asm_puts(int c);

asm_puts:
    push rbp
    mov rbp, rsp  ; Setup stack
    push rdi ; store rdi value in stack
    push r13 ; clears r13

    call asm_strlen
    pop rdi ; retrieve rdi
    push rdi ; store it again
    mov r13, rax ; move rax value into r13
    mov rax, 1 
    mov rsi, [rsp] ; moves top of stack into rsi
    mov rdx, r13 ; moves value in r13 into rdx
    syscall

    pop rdi
    mov rax, r13
    pop r13
    pop rbp
    ret ; exit