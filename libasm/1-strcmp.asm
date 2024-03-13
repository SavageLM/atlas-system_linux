BITS 64

    global asm_strcmp  ; EXPORT function

    section .text

    ; int asm_strcmp(const char *s1, const char *s2);

asm_strcmp:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start

asm_strcmp_next:
    cmp dil, 0x00
    jz asm_strcmp_null
    cmp dil, sil ; checks if bytes are same
    jl asm_strcmp_pos ; jumps to end for positive diff
    jg asm_strcmp_neg ; jumps to end for negative diff
    inc rdi
    inc rsi ; incrementing strings
    jmp asm_strcmp_next; Loop

asm_strcmp_null:
    cmp dil, sil
    jl asm_strcmp_neg
    xor rax, rax
    jmp asm_strcmp_end
asm_strcmp_neg:
    sub rax, 1
    jmp asm_strcmp_end

asm_strcmp_pos:
    add rax, 1
    jmp asm_strcmp_end

asm_strcmp_end:
    pop rbp
    ret ; exit