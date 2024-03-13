BITS 64

    global asm_strchr  ; EXPORT function

    section .text

    ; char *asm_strchr(const char *s, int c);

asm_strchr:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start

asm_strchr_next:
    cmp dil, sil ; checks if bytes are same
    jz asm_strchr_match
    cmp dil, 0x00
    jz asm_strchr_end
    inc rdi
    jmp asm_strchr_next; Loop

asm_strchr_match:
    mov rax, dil

asm_strchr_end:
    pop rbp
    ret ; exit