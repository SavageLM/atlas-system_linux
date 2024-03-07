BITS 64

    global asm_strlen  ; EXPORT function

    section .text

    ; size_t asm_strlen(const char *str);

a_strlen:
    push rbp
    mov rbp, rsp  ; Setup stack

    push rcx ; saves rcx count
    xor rcx, rcx ; resets rcx to 0
asm_strlen_next:
    cmp [rdi], byte 0 ; checks if null
    jz asm_strlen_null ; jumps to end if null
    inc rcx ; if not null increment count
    inc rdi ; move to next byte
    jmp asm_strlen_next ; repeat

asm_strlen_null:
    mov rax, rcx ; move count to rax
    pop rcx ; restore rcx
    ret ; exit