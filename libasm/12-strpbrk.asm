BITS 64

    global asm_strpbrk  ; EXPORT function

    section .text

    ; char *asm_strpbrk(const char *s, const char *accept);

asm_strpbrk:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start

asm_strpbrk_next:
    cmp rdi, rsi ; checks if bytes are same
    jz asm_strpbrk_match
    cmp byte [rdi], 0
    jz asm_strpbrk_end
    inc rdi
    jmp asm_strpbrk_next; Loop

asm_strpbrk_match:
    mov rax, rdi

asm_strpbrk_end:
    pop rbp
    ret ; exit