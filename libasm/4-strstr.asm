BITS 64

    global asm_strstr  ; EXPORT function

    section .text

    ; int char *asm_strstr(const char *haystack, const char *needle);

asm_strstr:
    push rbp
    mov rbp, rsp  ; Setup stack
    xor rcx, rcx ; sets counter to 0
asm_strstr_search:
    push rsi
    cmp rdi, rsi ; checks if bytes are same
    jz substr_start ; if match, jump to check substring
    cmp byte [rdi], 0 ; check if rdi is NULL
    jz asm_strstr_null ; jumps if rdi is NULL
    inc rdi
    jmp asm_strstr_search; Loop

substr_start:
    xor rax, rax ; make sure rax is clear
    cmp byte [rdi], 0 ; check if rdi is NULL
    jz asm_strstr_null ; jumps if rdi is NULL
    mov rax, rdi ; sets start position of substring
    jmp substr_loop ; jumps to lopping substr

substr_loop:
    inc rdi
    inc rsi
    cmp rdi, rsi ; check if still match
    jz substr_loop ; loops back
    cmp byte [rsi], 0 ; check if end of substring
    jz asm_strstr_end
    cmp byte [rdi], 0 ; check if rdi is NULL
    jz asm_strstr_null ; jumps if rdi is NULL
    pop rsi ; resotres rsi on a non-match
    jmp asm_strstr_search ; starts search over


asm_strstr_null:
    xor rax, rax ; set rax to 0
    jmp asm_strstr_end

asm_strstr_end:
    pop rbp
    ret ; exit