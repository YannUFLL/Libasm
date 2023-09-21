bits 64


section .text
    global ft_strcpy
        ft_strcpy:

        ; dest rdi
        ; src rci 
        push rdi
        main_loop:
            mov al, byte [rsi]
            mov byte [rdi], al
            test al, al
            jz return
            inc rdi
            inc rsi
            jmp main_loop

        return:
            pop rdi
            mov rax, rdi 
            ret

        ; rdi char dest 
        ; rsi char srcs 