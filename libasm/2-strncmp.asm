BITS 64

    global asm_strncmp  ; EXPORT function

    section .text

    ; int asm_strncmp(const char *s1, const char *s2, size_t n);

asm_strncmp:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start
    xor rcx, rcx ; resets rcx to 0

asm_strncmp_next:
    cmp rdi, rsi ; checks if bytes are same
    ja asm_strncmp_pos ; jumps to end for positive diff
    jb asm_strncmp_neg ; jumps to end for negative diff
    cmp byte [rdi], 0
    jz asm_strncmp_null
    cmp rdx, rcx
    jz asm_strncmp_end
    inc rdi
    inc rsi ; incrementing strings
    inc rcx ; increment loop count
    jmp asm_strncmp_next; Loop

asm_strncmp_null:
    cmp byte [rsi], 0
    xor rax, rax
    jmp asm_strncmp_end
asm_strncmp_neg:
    add rax, -1
    jmp asm_strncmp_end

asm_strncmp_pos:
    add rax, 1
    jmp asm_strncmp_end

asm_strncmp_end:
    pop rbp
    ret ; exit