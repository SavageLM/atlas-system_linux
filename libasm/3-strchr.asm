BITS 64

    global asm_strchr  ; EXPORT function

    section .text

    ; char *asm_strchr(const char *s, int c);

asm_strchr:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start
    xor rcx, rcx

asm_strchr_next:
    movzx ecx, byte [rdi]
    cmp cl, sil ; checks if bytes are same
    jz asm_strchr_match
    inc rdi
    cmp cl, 0x00
    jnz asm_strchr_next; Loop
    jz asm_strchr_end

asm_strchr_match:
    mov rax, rdi
    jmp asm_strchr_end

asm_strchr_end:
    pop rbp
    ret ; exit