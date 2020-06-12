# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jheeresm <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/04 13:29:01 by jheeresm       #+#    #+#                 #
#    Updated: 2019/11/12 22:37:21 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CW_NAME =		corewar

OP_FILES =		fork lfork zjmp add aff and ld ldi \
				live lld lldi or st sti sub xor operation_help

CW_FILES =		main check_arguments input_error init_champion audio \
				exec_cursor_list read_operation save_arguments init_cursors \
				load_champs endianness dump_flag game reset_operation \
				introduce_champions init_vm verbose timing visualizer \
				change_colors init_visualizer arguments_help \
				$(OP_FILES:%=operations/%)

CW_SRC =		$(CW_FILES:%=srcs/%.c)

LIBFT =			../libft/libft.a

CW_OBJ =		$(CW_SRC:.c=.o)

FLAGS =			-g -Wall -Wextra -Werror

all : $(CW_NAME)

$(CW_NAME) : $(CW_OBJ) $(LIBFT)
				@ gcc $(FLAGS) -o $@ $(CW_OBJ) -L . -lbass -lncurses -L \
				../libft -lft
				@ echo "\033[32mCOREWAR READY\033[0m"

$(LIBFT) :
	 			@ make -C ../libft/

srcs/%.o : srcs/%.c includes/corewar.h
				@ gcc $(FLAGS) $< -c -o $@

clean :
				@ if [ `ls -1 srcs/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ `ls -1 srcs/operations/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ `ls -1 ../libft/*.o 2>/dev/null | wc -l ` -gt 0 ]; then \
				make clean -C ../libft/; \
				rm -f $(CW_OBJ); \
				echo "\033[33mCLEAN COMPLETED\033[0m"; else \
				echo "\033[33mNOTHING TO CLEAN\033[0m"; fi

fclean :
				@ if [ `ls -1 srcs/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ `ls -1 srcs/operations/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ `ls -1 ../libft/*.o 2>/dev/null | wc -l ` -gt 0 ] || \
				[ -f $(CW_NAME) ] || [ -f ../libft/libft.a ]; then \
				make fclean -C ../libft/ && rm -f $(CW_NAME) && \
				rm -f $(CW_OBJ); \
				echo "\033[33mCLEAN COMPLETED\033[0m"; else \
				echo "\033[33mNOTHING TO CLEAN\033[0m"; fi

re : fclean all

.PHONY: clean fclean all re
