# ASM source files
ASM_SRC := $(wildcard asm/*.asm)

# Corresponding object files in the obj directory
ASM_OBJ := $(patsubst asm/%.asm, obj/%.o, $(ASM_SRC))

# C source files
C_SRC := $(wildcard *.c)

# Corresponding object files
C_OBJ := $(patsubst %.c, obj/%.o, $(C_SRC))

# Final executable file
EXEC := test

# Library name
LIBASM := libasm

# Compilation flags
CFLAGS = -I include -Wall -Wextra -Werror 

all: $(EXEC)

# Rule to compile ASM files
obj/%.o: asm/%.asm
	nasm -f elf64 -g -F dwarf $< -o $@

# Rule to create the library
$(LIBASM).a: $(ASM_OBJ)
	ar rcs $(LIBASM).a $^

# Rule to compile C files
obj/%.o: %.c
	gcc $(CFLAGS) -g -c $< -o $@


# Rule for the final executable
$(EXEC): $(LIBASM).a $(C_OBJ)
	gcc $^ -L. -lasm -o $@ 

# Rule to clean object files
clean:
	rm -f $(ASM_OBJ) $(C_OBJ) test_close_fd test_ft_write.txt test_std_write.txt

# Rule to clean everything (object files + executable)
fclean: clean
	rm -f $(EXEC) $(LIBASM).a

# Rule to recompile everything
re: fclean all 

.PHONY: clean fclean re 
