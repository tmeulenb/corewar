/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   disassembler.h                                      :+:    :+:           */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/24 11:55:05 by jheeresm       #+#    #+#                */
/*   Updated: 2019/10/24 21:18:25 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASSEMBLER_H
# define DISASSEMBLER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include "op.h"
# include "../../libft/libft.h"

typedef enum		e_operation
{
	live = 1,
	ld = 2,
	st = 3,
	add = 4,
	sub = 5,
	and = 6,
	or = 7,
	xor = 8,
	zjmp = 9,
	ldi = 10,
	sti = 11,
	fork_ = 12,
	lld = 13,
	lldi = 14,
	lfork = 15,
	aff = 16
}					t_operation;

# define ARG_1			exec->arg[0]
# define ARG_2			exec->arg[1]
# define ARG_3			exec->arg[0]

typedef struct			s_exec
{
	t_header			header;
	unsigned char		*code;
	int					op_code;
	int					arg[3];
	int					octet[16];
	int					t_dir[16];
}						t_exec;

void					init_octet(t_exec *exec);
void					init_t_dir(t_exec *exec);
void					init_exec(t_exec *exec);

/*
**						error_messaging.c
*/

void					error_messaging(int choice);

/*
**						disassemble_file.c
*/

void					disassemble_file(char *filename);
void					check_if_return_of_read_is_valid(int ret,
														int bytes_to_read);
/*
**						get_null.c
*/

void					get_null(int fd);

/*
**						get_champion_exec_code.c
*/

void					get_champion_exec_code(int fd, t_exec *exec);

/*
**						create_file_dot_s.c
*/

int						create_file_dot_s(char *filename);

/*
**						disassemble_exec_code.c
*/

void					disassemble_exec_code(int fd, t_exec *exec);

/*
**						get_arguments.c
*/

void					get_arguments(int fd, t_exec *exec, int *pos);

/*
**						print_buff.c
*/

void					print_buff(unsigned char *buff, int prog_size);

#endif
