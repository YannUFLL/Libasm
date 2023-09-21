bits 64 

section .text 
    extern ft_strlen
    extern ft_strcpy
    extern malloc
    global ft_strdup
        ft_strdup: 


        push rax
        call ft_strlen
        mov rdi, rax 
        inc rdi
        call malloc wrt ..plt
        test rax, rax 
        js error 
        mov rdi, rax 
        pop rsi 
        call ft_strcpy 
        jmp return


        error: 
            mov rax, -1
            ret
        return: 
            ret