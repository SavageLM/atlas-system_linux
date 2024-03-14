BITS 64

    global asm_strcspn  ; EXPORT function

    section .text

    ; size_t asm_strcspn(const char *s, const char *reject);

asm_strcspn:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start

asm_strcspn_next:
    cmp rdi, rsi ; checks if bytes are same
    jz asm_strcspn_match
    cmp byte [rdi], 0
    jz asm_strcspn_end
    inc rdi
    jmp asm_strcspn_next; Loop

asm_strcspn_match:
    mov rax, rdi

asm_strcspn_end:
    pop rbp
    ret ; exit