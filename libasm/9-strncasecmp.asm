BITS 64

    global asm_strncasecmp  ; EXPORT function

    section .text

    ; int asm_strncasecmp(const char *s1, const char *s2);

asm_strncasecmp:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start

asm_strncasecmp_next:
    cmp rdx, 0
    jz asm_strncasecmp_end
    mov rax, rdi
	mov rcx, rsi
	movzx eax, BYTE [rax]
	movzx edx, BYTE [rdx]
    cmp al, 0x00
    jz asm_strncasecmp_null
    cmp al, 65 ; compares char to 'A'
    jl asm_strncasecmp_cnvt ; if less, is not a letter
    cmp al, 90 ;  compares char to 'Z'
    jg asm_strncasecmp_cnvt ; if greater is already lowercase, or not a letter
    add al, 32 ; changes letter to lowercase
    jmp asm_strncasecmp_cnvt

asm_strncasecmp_cnvt:
    cmp cl, 0x00
    jz asm_strncasecmp_null
    cmp cl, 65 ; compares char to 'A'
    jl asm_strncasecmp_cmp ; if less, is not a letter
    cmp cl, 90 ;  compares char to 'Z'
    jg asm_strncasecmp_cmp ; if greater is already lowercase, or not a letter
    add cl, 32 ; changes letter to lowercase
    jmp asm_strncasecmp_cmp

asm_strncasecmp_cmp:
    cmp al, dl ; checks if bytes are same
    ja asm_strncasecmp_pos ; jumps to end for positive diff
    jb asm_strncasecmp_neg ; jumps to end for negative diff
    inc rdi
    inc rsi ; incrementing strings
    dec rdx
    jmp asm_strncasecmp_next; Loop

asm_strncasecmp_null:
    cmp dl, 0x00
    jl asm_strncasecmp_neg
    xor rax, rax
    jmp asm_strncasecmp_end
asm_strncasecmp_neg:
    sub rax, 1
    jmp asm_strncasecmp_end

asm_strncasecmp_pos:
    add rax, 1
    jmp asm_strncasecmp_end

asm_strncasecmp_end:
    pop rbp
    ret ; exit