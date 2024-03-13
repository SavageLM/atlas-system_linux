BITS 64

    global asm_strstr  ; EXPORT function

    section .text

    ; int char *asm_strstr(const char *haystack, const char *needle);

asm_strstr:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rcx, rcx ; sets counter to 0
    xor rdx, rdx ; set counter to 0
asm_strstr_search:
    push rsi
    movzx ecx, byte [rdi]
    cmp cl, sil ; checks if bytes are same
    jz substr_start ; if match, jump to check substring
    cmp cl, 0x00 ; check if rdi is NULL
    jz asm_strstr_null ; jumps if rdi is NULL
    inc rdi
    jmp asm_strstr_search; Loop

substr_start:
    xor rax, rax ; make sure rax is clear
    cmp cl, 0x00 ; check if rdi is NULL
    jz asm_strstr_null ; jumps if rdi is NULL
    mov rax, rdi ; sets start position of substring
    jmp substr_loop ; jumps to lopping substr

substr_loop:
    inc rdi
    inc rsi
    movzx ecx, byte [rdi]
    cmp cl, sil ; check if still match
    jz substr_loop ; loops back
    cmp sil, 0x00 ; check if end of substring
    jz asm_strstr_end
    cmp cl, 0x00 ; check if rdi is NULL
    jz asm_strstr_null ; jumps if rdi is NULL
    pop rsi ; resotres rsi on a non-match
    jmp asm_strstr_search ; starts search over


asm_strstr_null:
    xor rax, rax ; set rax to 0
    mov rax, rdi ; set rax to NULL pointer
    jmp asm_strstr_end

asm_strstr_end:
    pop rbp
    ret ; exit