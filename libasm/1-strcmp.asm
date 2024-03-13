BITS 64

    global asm_strcmp  ; EXPORT function

    section .text

    ; int asm_strcmp(const char *s1, const char *s2);

asm_strcmp:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start

asm_strcmp_next:
    cmp dil, sil ; checks if bytes are same
    ja asm_strcmp_pos ; jumps to end for positive diff
    jb asm_strcmp_neg ; jumps to end for negative diff
    cmp dil, 0
    jz asm_strcmp_null
    inc rdi
    inc rsi ; incrementing strings
    jmp asm_strcmp_next; Loop

asm_strcmp_null:
    cmp sil, 0x00
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