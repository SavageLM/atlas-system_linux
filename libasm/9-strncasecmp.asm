BITS 64

    global asm_strncasecmp  ; EXPORT function

    section .text

    ; int asm_strncasecmp(const char *s1, const char *s2);

asm_strncasecmp:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rax, rax ; ensures rax is 0 at start
    push rbx
    push rcx

asm_strncasecmp_next:
    cmp rdx, 0
    jz asm_strncasecmp_ne
	movzx ebx, BYTE [rdi]
	movzx ecx, BYTE [rsi]
    cmp bl, 0x00
    jnz asm_strncasecmp_bl_cnvt
    cmp cl, 0x00
    jnz asm_strncasecmp_cl_cnvt
    jmp asm_strncasecmp_ne

asm_strncasecmp_bl_cnvt:
    cmp bl, 65 ; compares char to 'A'
    jl asm_strncasecmp_cl_cnvt ; if less, is not a letter
    cmp bl, 90 ;  compares char to 'Z'
    jg asm_strncasecmp_cl_cnvt ; if greater is already lowercase, or not a letter
    add bx, 32 ; changes letter to lowercase
    jmp asm_strncasecmp_cl_cnvt

asm_strncasecmp_cl_cnvt:
    cmp cl, 65 ; compares char to 'A'
    jl asm_strncasecmp_cmp ; if less, is not a letter
    cmp cl, 90 ;  compares char to 'Z'
    jg asm_strncasecmp_cmp ; if greater is already lowercase, or not a letter
    add cx, 32 ; changes letter to lowercase
    jmp asm_strncasecmp_cmp

asm_strncasecmp_cmp:
    cmp bl, cl ; checks if bytes are same
    jnz asm_strncasecmp_ne ; jumps to end for positive diff
    inc rdi
    inc rsi ; incrementing strings
    dec rdx
    jmp asm_strncasecmp_next; Loop

asm_strncasecmp_ne:
    sub rbx, rcx
    mov rax, rbx

    pop rcx
    pop rbx
    pop rbp
    ret ; exit