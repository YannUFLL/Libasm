bits 64 

SYS_READ equ 0

section .text
    extern __errno_location
    global ft_read
        ft_read: 

        mov rax, SYS_READ
        syscall 
        test rax, rax 
        js error    
        ret 

        error: 
        neg rax
        mov rdi, rax 
        call __errno_location wrt ..plt 
        mov [rax], rdi
        mov rax, -1 
        ret 