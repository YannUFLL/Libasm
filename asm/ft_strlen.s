bits 64 

section .text 
    global ft_strlen
    ft_strlen: 

    xor rax, rax
    test rdi, rdi
    JZ return

    count_length:
        xor rcx, rcx 
        loop_: 
            mov al, [rdi]
            test al, al
            jz return
            inc rcx
            inc rdi
            jnz loop_
    return:
        mov rax, rcx
        ret