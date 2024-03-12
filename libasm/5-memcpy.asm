BITS 64

    global asm_memcpy  ; EXPORT function

    section .text

    ; void *asm_memcpy(void *dest, const void *src, size_t n);

asm_memcpy:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start
    push rdi ; store rdi value in stack

asm_memcpy_loop:
    test rdx, rdx ; performs AND operation
    jz asm_memcpy_end ; jumps to end
    mov al, byte [rsi] ; moves byte from source to al
    mov byte [rdi], al ; move byte from al to dest
    dec rdx ; decrease number of moves left
    inc rdi
    inc rsi ; incrementing strings
    jmp asm_memcpy_loop; Loop

asm_memcpy_end:
    pop rax
    pop rbp
    ret ; exit