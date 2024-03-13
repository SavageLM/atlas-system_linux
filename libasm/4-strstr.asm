BITS 64

    global asm_strstr  ; EXPORT function

    section .text

    ; int char *asm_strstr(const char *haystack, const char *needle);

asm_strstr:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rcx, rcx ; sets counter to 0
    xor rdx, rdx ; set counter to 0
    push r13
    movzx edx, byte [rsi]
    cmp dl, 0x00
    jz asm_strstr_null
asm_strstr_search:
    mov r13, rsi
    movzx ecx, byte [rdi]
    movzx edx, byte [r13]
    cmp cl, dl ; checks if bytes are same
    jz substr_start ; if match, jump to check substring
    cmp cl, 0x00 ; check if rdi is NULL
    jz asm_strstr_nf ; jumps if rdi is NULL
    inc rdi
    jmp asm_strstr_search; Loop

substr_start:
    xor rax, rax ; make sure rax is clear
    mov rax, rdi ; sets start position of substring
    cmp cl, 0x00 ; check if rdi is NULL
    jz asm_strstr_nf ; jumps if rdi is NULL
    jmp substr_loop ; jumps to lopping substr

substr_loop:
    inc rdi
    inc r13
    movzx ecx, byte [rdi]
    movzx edx, byte [r13]
    cmp dl, 0x00 ; check if end of substring
    jz asm_strstr_end
    cmp cl, 0x00 ; check if rdi is NULL
    jz asm_strstr_nf ; jumps if rdi is NULL
    cmp cl, dl ; check if still match
    jz substr_loop ; loops back
    jmp asm_strstr_search ; starts search over

asm_strstr_nf:
    xor rax, rax
    jmp asm_strstr_end

asm_strstr_null:
    xor rax, rax ; set rax to 0
    mov rax, rdi ; set rax to NULL pointer
    jmp asm_strstr_end

asm_strstr_end:
    pop r13
    pop rbp
    ret ; exit