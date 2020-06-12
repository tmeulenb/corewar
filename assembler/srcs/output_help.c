/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output_help.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 13:52:58 by jheeresm       #+#    #+#                */
/*   Updated: 2019/10/11 18:49:50 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

void	write_instr(t_tokens *token, int fd)
{
	char oct;
	char inst;

	inst = (char)token->instruction;
	write(fd, &inst, 1);
	if (oct_check(token->instruction))
	{
		oct = get_coding_oct(token, token->instruction);
		write(fd, &oct, 1);
	}
}

void	write_regist(t_tokens *token, int fd)
{
	char value;

	value = (char)token->value;
	write(fd, &value, 1);
}

void	write_direct(t_tokens *token, int fd, t_instruction inst)
{
	static int				direct_size[16] =
	{4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4};

	if (direct_size[inst - 1] == 4)
	{
		token->value = reverse32(token->value);
		write(fd, &(token->value), 4);
	}
	else
	{
		token->value = reverse16(token->value);
		write(fd, &(token->value), 2);
	}
}

void	write_indirect(t_tokens *token, int fd)
{
	token->value = reverse16(token->value);
	write(fd, &(token->value), 2);
}
