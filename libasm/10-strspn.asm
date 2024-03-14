BITS 64

    global asm_strspn  ; EXPORT function

    section .text

    ; size_t asm_strspn(const char *s, const char *accept);

asm_strspn:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start

asm_strspn_next:
    cmp rdi, rsi ; checks if bytes are same
    jz asm_strspn_match
    cmp byte [rdi], 0
    jz asm_strspn_end
    inc rdi
    jmp asm_strspn_next; Loop

asm_strspn_match:
    mov rax, rdi

asm_strspn_end:
    pop rbp
    ret ; exit