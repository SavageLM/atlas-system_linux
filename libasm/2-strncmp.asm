BITS 64

    global asm_strncmp  ; EXPORT function

    section .text

    ; int asm_strncmp(const char *s1, const char *s2, size_t n);

asm_strncmp:
    push rbp
    mov rbp, rsp  ; Setup stack
    push rbx

asm_strncmp_next:
    movzx ebx, byte [rdi]
    movzx eax, byte [rsi]
    cmp bl, 0x00
    jz asm_strncmp_null
    cmp bl, al ; checks if bytes are same
    jg asm_strncmp_pos ; jumps to end for positive diff
    jl asm_strncmp_neg ; jumps to end for negative diff
    inc rdi
    inc rsi ; incrementing strings
    dec rdx
    cmp rdx, 0
    jz asm_strncmp_null
    jmp asm_strncmp_next; Loop

asm_strncmp_null:
    cmp bl, al
    jl asm_strncmp_neg
    xor rax, rax
    jmp asm_strncmp_end
asm_strncmp_neg:
    mov rax, -1
    jmp asm_strncmp_end

asm_strncmp_pos:
    mov rax, 1
    jmp asm_strncmp_end

asm_strncmp_end:
    pop rbx
    pop rbp
    ret ; exit