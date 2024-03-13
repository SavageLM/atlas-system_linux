BITS 64

    global asm_strcasecmp  ; EXPORT function

    section .text

    ; int asm_strcasecmp(const char *s1, const char *s2);

asm_strcasecmp:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start
    push r13

asm_strcasecmp_next:
    mov rax, rdi
	mov rdx, rsi
	movzx eax, BYTE [rax]
	movzx edx, BYTE [rdx]
    cmp al, 0x00
    jz asm_strcasecmp_null
    cmp al, 65 ; compares char to 'A'
    jl asm_strcasecmp_cmp ; if less, is not a letter
    cmp al, 90 ;  compares char to 'Z'
    jg asm_strcasecmp_cmp ; if greater is already lowercase, or not a letter
    add ax, 32 ; changes letter to lowercase
    jmp asm_strcasecmp_cmp

asm_strcasecmp_cmp:
    cmp al, dl ; checks if bytes are same
    ja asm_strcasecmp_pos ; jumps to end for positive diff
    jb asm_strcasecmp_neg ; jumps to end for negative diff
    inc rdi
    inc rsi ; incrementing strings
    jmp asm_strcasecmp_next; Loop

asm_strcasecmp_null:
    cmp dl, 0x00
    jl asm_strcasecmp_neg
    xor rax, rax
    jmp asm_strcasecmp_end
asm_strcasecmp_neg:
    sub rax, 1
    jmp asm_strcasecmp_end

asm_strcasecmp_pos:
    add rax, 1
    jmp asm_strcasecmp_end

asm_strcasecmp_end:
    pop rbp
    ret ; exit