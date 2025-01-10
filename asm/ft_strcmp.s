bits 64 

section .text  
    global ft_strcmp
        ft_strcmp: 

        ;rdi 1er argument 
        ;rsi 2eme argument 
        cmp_loop:
            xor rax, rax
            mov al, byte [rdi]
            mov dl, byte [rsi]

            cmp al, dl
            jg greater
            jl lower
            test al, al
            jz end_string

            inc rdi
            inc rsi
            jmp cmp_loop
        
        end_string:
            test dl, dl
            jz equal
            jnz lower 

        greater: 
            mov rax, 1
            ret

        lower:
            mov rax, -1
            ret 

        equal: 
            mov rax, 0
            ret