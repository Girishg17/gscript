section .data
msg1 db "Checking age...", 10, 0
msg2 db "Adult", 10, 0
msg3 db "Minor", 10, 0
section .text
global _start
_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg1
    mov rdx, 16
    syscall

    mov rbx, 20  ; age
    cmp rbx, 18
    jg label1
    jmp label2
label1:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg2
    mov rdx, 6
    syscall

label2:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg3
    mov rdx, 6
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall
