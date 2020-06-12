# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jheeresm <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/04 13:29:01 by jheeresm       #+#    #+#                 #
#    Updated: 2019/11/12 21:15:05 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

ASM_NAME =		asm

ASM_FILES =		main parser tools tokens analyze analyze_help check_arguments \
				endian output get_coding_oct output_help

ASM_SRC =		$(ASM_FILES:%=srcs/%.c)

LIBFT =			../libft/libft.a

ASM_OBJ =		$(ASM_SRC:.c=.o)

FLAGS =			-g -Wall -Wextra -Werror

all : $(ASM_NAME)

$(ASM_NAME) : $(ASM_OBJ) $(LIBFT)
				@ gcc $(FLAGS) -o $@ $(ASM_OBJ) -L ../libft -lft
				@ echo "\033[32mASSEMBLER READY\033[0m"

$(LIBFT) :
	 			@ make -C ../libft/

srcs/%.o : srcs/%.c includes/assembler.h includes/op.h
				@ gcc $(FLAGS) $< -c -o $@

clean :
				@ if [ `ls -1 srcs/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ `ls -1 ../libft/*.o 2>/dev/null | wc -l ` -gt 0 ]; then \
				make clean -C ../libft/ && rm -f $(ASM_OBJ); \
				echo "\033[33mCLEAN COMPLETED\033[0m"; else \
				echo "\033[33mNOTHING TO CLEAN\033[0m"; fi

fclean :
				@ if [ `ls -1 srcs/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ `ls -1 ../libft/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ -f $(ASM_NAME) ] || [ -f ../libft/libft.a ]; then \
				make fclean -C ../libft/ && rm -f $(ASM_NAME) && \
				rm -f $(ASM_OBJ); \
				echo "\033[33mCLEAN COMPLETED\033[0m"; else \
				echo "\033[33mNOTHING TO CLEAN\033[0m"; fi

re : fclean all

.PHONY: clean fclean all re
