# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jheeresm <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/04 13:29:01 by jheeresm       #+#    #+#                 #
#    Updated: 2019/11/12 21:11:18 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CW_NAME =		dis_asm


CW_FILES =		main \
				disassemble_file \
				error_messaging \
				check_if_return_of_read_is_valid \
				get_null \
				get_champion_exec_code \
				create_file_dot_s \
				disassemble_exec_code \
				get_arguments \
				init

CW_SRC =		$(CW_FILES:%=srcs/%.c)

LIBFT =			../libft/libft.a

CW_OBJ =		$(CW_SRC:.c=.o)

FLAGS =			-g -Wall -Wextra -Werror

all : $(CW_NAME)

$(CW_NAME) : 	$(LIBFT) $(CW_OBJ) 
				@ gcc $(FLAGS) -o $@ $(CW_OBJ) -L ../libft -lft
				@ echo "\033[32mDISASSEMBLER READY\033[0m"

$(LIBFT) :
	 			@ make -C ../libft/

srcs/%.o : srcs/%.c includes/disassembler.h
				@ gcc $(FLAGS) $< -c -o $@

clean :
				@ if [ `ls -1 srcs/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ `ls -1 ../libft/*.o 2>/dev/null | wc -l ` -gt 0 ]; then \
				make clean -C ../libft/; \
				rm -f $(CW_OBJ); \
				echo "\033[33mCLEAN COMPLETED\033[0m"; else \
				echo "\033[33mNOTHING TO CLEAN\033[0m"; fi

fclean :
				@ if [ `ls -1 srcs/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ `ls -1 libft/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ -f $(CW_NAME) ] || [ -f ../libft/libft.a ]; then \
				make fclean -C ../libft/ && rm -f $(CW_NAME) && \
				rm -f $(CW_OBJ); \
				echo "\033[33mCLEAN COMPLETED\033[0m"; else \
				echo "\033[33mNOTHING TO CLEAN\033[0m"; fi

re : clean fclean all

.PHONY: clean fclean all re
