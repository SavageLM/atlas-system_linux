BITS 64

    global asm_strcmp  ; EXPORT function

    section .text

    ; int asm_strcmp(const char *s1, const char *s2);

asm_strcmp:
    push rbp
    mov rbp, rsp  ; Setup stack
    push rbx

asm_strcmp_next:
    movzx ebx, byte [rdi]
    movzx eax, byte [rsi]
    cmp bl, 0x00
    jz asm_strcmp_null
    cmp bl, al ; checks if bytes are same
    jg asm_strcmp_pos ; jumps to end for positive diff
    jl asm_strcmp_neg ; jumps to end for negative diff
    inc rdi
    inc rsi ; incrementing strings
    jmp asm_strcmp_next; Loop

asm_strcmp_null:
    cmp bl, al
    jl asm_strcmp_neg
    xor rax, rax
    jmp asm_strcmp_end
asm_strcmp_neg:
    mov rax, -1
    jmp asm_strcmp_end

asm_strcmp_pos:
    mov rax, 1
    jmp asm_strcmp_end

asm_strcmp_end:
    pop rbx
    pop rbp
    ret ; exit