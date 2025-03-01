global main
extern printf
extern scanf
extern system
 
SECTION .data
Format db "Please enter admin:",0
aS db "%s",0
byte_404012 db "Please enter password:",0
Command db "pause",0
string1 db "Error!!!",0
string2 db "OK!",0
Admin db "admin",0
Password db "123456",0
 
SECTION .bss
username resb 50
password resb 50
 
SECTION .text
main:
    push rbp
    mov rbp, rsp
    sub rsp, 190

    lea rcx, [Format]
    call printf

    lea rdx, [username]
    lea rcx, [aS]
    call scanf

    lea rcx, [byte_404012]
    call printf

    lea rdx, [password]
    lea rcx, [aS]
    call scanf

    lea rsi, [Admin]
    lea rdi, [username]
    call compare_strings
    cmp rax, 1
    jne error

    lea rsi, [Password]
    lea rdi, [password]
    call compare_strings
    cmp rax, 1
    jne error
 
    lea rcx, [string2]
    call printf
    jmp end
 
compare_strings:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    xor rax, rax
    xor rcx, rcx
loop_compare:
    mov dl, [rsi + rcx]
    mov al, [rdi + rcx]
    cmp dl, al
    jne not_l
    cmp dl, 0
    je l
    inc rcx
    jmp loop_compare
 
not_l:
    mov rax, 0
    leave
    ret
 
l:
    mov rax, 1
    leave
    ret
 
end:
    lea rcx, [Command]
    call system
 
    mov eax, 0
    add rsp, 190
    pop rbp
    ret
 
error:
    lea rcx, [string1]
    call printf
    jmp end
 